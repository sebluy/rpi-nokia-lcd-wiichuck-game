#include <unistd.h>
#include <math.h>

#include "character.h"
#include "lcd_display.h"
#include "wii_chuck.h"
#include "world.h"

#define WIDTH WORLD_WIDTH
#define HEIGHT WORLD_HEIGHT

#define ADD 1
#define REMOVE 0

#define DELAY 16667 /* 60 Hz */

static unsigned char GRID[HEIGHT][WIDTH] ;

static void change_character(character *c, int add) ;

static void add_platform(int x, int y, int length) ;

static int grid_y(int y) ;
static int value_at(int x, int y) ;
static void set_value_at(int x, int y, int value) ;

static double search_platform_right(double x, double y,
		int height, double max_distance) ;
static double search_platform_left(double x, double y,
		int height, double max_distance) ;
static double search_platform_down(double x, double y,
		int width, double max_distance) ;
static double search_platform_up(double x, double y,
		int width, double max_distance) ;

static int search_col(int x, int y, int length) ;
static int search_row(int x, int y, int width) ;

void world_add_character(character *c)
{		
	change_character(c, ADD) ;
}

void world_remove_character(character *c)
{
	change_character(c, REMOVE) ;
}

int world_character_grounded(character *c)
{
	return search_row(c->pos_x, c->pos_y - 1, CHARACTER_WIDTH) ;
	
}

void world_character_limit_vel(character *c)
{
	/* stay in world */

	/* y bounds */
	if ((c->pos_y + c->vel_y) < 0)
		c->vel_y = -(c->pos_y) ;
	else if ((c->pos_y + CHARACTER_HEIGHT + c->vel_y) > HEIGHT - 1)
		c->vel_y = (HEIGHT - 1 - c->pos_y - CHARACTER_HEIGHT) ;

	/* x bounds */
	if ((c->pos_x + c->vel_x) < 0)
		c->vel_x = -(c->pos_x) ;
	else if ((c->pos_x + CHARACTER_WIDTH + c->vel_x) > WIDTH - 1)
		c->vel_x = (WIDTH - 1 - c->pos_x - CHARACTER_WIDTH) ;

	double distance ;

	/* diagonal collisions */
	/* up right */
	/*
	if (c->vel_y > 0 && c->vel_x > 0) {
		distance = search_platform_right(c->pos_x + CHARACTER_WIDTH,
				c->pos_y + CHARACTER_HEIGHT, c->vel_y + 1, c->vel_x + 1) ;
		if (distance >= 0) {
			c->vel_x = 0 ;
			c->vel_y = 0 ;
		}
	}
	*/

	/* down right */
	/*
	if (c->vel_y < 0 && c->vel_x > 0) {
		distance = search_platform_right(c->pos_x + CHARACTER_WIDTH,
				c->pos_y - c->vel_y + 1, c->vel_y + 1, c->vel_x + 1) ;
		if (distance >= 0) {
			c->vel_x = 0 ;
			c->vel_y = 0 ;
		}
	}
	*/

	/* x collisions */
	if (c->vel_x > 0) {
		distance = search_platform_right(c->pos_x + CHARACTER_WIDTH,
				c->pos_y, CHARACTER_HEIGHT, c->vel_x) ;
		if (distance >= 0)
			c->vel_x = distance ;
	} else if (c->vel_x < 0 ) {
		distance = search_platform_left(c->pos_x, c->pos_y,
				CHARACTER_HEIGHT, c->vel_x) ;
		if (distance <= 0)
			c->vel_x = distance ;
	}
	
	/* y collisions */
	if (c->vel_y < 0) {
		distance = search_platform_down(c->pos_x, c->pos_y,
				CHARACTER_WIDTH, c->vel_y) ;
		if (distance <= 0)
			c->vel_y = distance ;

	} else if (c->vel_y > 0) {
		distance = search_platform_up(c->pos_x,
			c->pos_y + CHARACTER_HEIGHT,
			CHARACTER_WIDTH, c->vel_y) ;
		if (distance >= 0)
			c->vel_y = distance ;
	}

}

static double search_platform_right(double x, double y,
		int height, double max_distance)
{
	int col ;
	int cols_searched ;
	col = x ;
	cols_searched = 0 ;
	while (cols_searched < max_distance + 1) {
		if (search_col(col, y, height))
			return col - x ;
		cols_searched++ ;
		col++ ;
	}
	return -1 ;
}

static double search_platform_left(double x, double y,
		int height, double max_distance)
{
	int col ;
	int cols_searched ;
	col = x - 1 ;
	cols_searched = 0 ;
	while (cols_searched > max_distance - 1) {
		if (search_col(col, y, height))
			return col - x + 1 ;
		cols_searched-- ;
		col-- ;
	}
	return 1 ;
}

static double search_platform_down(double x, double y,
		int width, double max_distance)
{
	int row ;
	int rows_searched ;
	row = y - 1 ;
	rows_searched = 0 ;
	while (rows_searched > max_distance - 1) {
		if (search_row(x, row, width))
			return row - y + 1 ;
		rows_searched-- ;
		row-- ;
	}
	return 1 ;
}

static double search_platform_up(double x, double y,
		int width, double max_distance)
{
	int row ;
	int rows_searched ;
	row = y ;
	rows_searched = 0 ;
	while (rows_searched < max_distance + 1) {
		if (search_row(x, row, width))
			return row - y ;
		rows_searched++ ;
		row++ ;
	}
	return -1 ;
}

static int search_col(int x, int y, int height)
{
	int i ;
	for (i = y ; i < y + height ; i++)
		if (value_at(x, i))
			return 1 ;
	return 0 ;
}

static int search_row(int x, int y, int width)
{
	int i ;
	for (i = x ; i < x + width ; i++)
		if (value_at(i, y))
			return 1 ;
	return 0 ;
}

void world_setup(void)
{
	add_platform(10, 10, 5) ;
	add_platform(20, 20, 5) ;
	add_platform(30, 30, 5) ;
	add_platform(40, 20, 5) ;
	add_platform(50, 20, 5) ;

	wii_chuck_setup() ;
	lcd_display_setup() ;
	lcd_display_clear() ;
	lcd_display_update() ;
}

void world_update(void)
{
	usleep(DELAY) ;
	character_update() ;
	lcd_display_map(GRID) ;
	lcd_display_update() ;
}

static void change_character(character *c, int add)
{
	int i, j, value ;
	for (j = 0 ; j < CHARACTER_HEIGHT ; j++) {
		for (i = 0 ; i < CHARACTER_WIDTH ; i++) {
			value = add ? character_value_at(i, j) : 0 ;
			set_value_at(c->i_pos_x + i, c->i_pos_y + j, value) ;
		}
	}
}

static void add_platform(int x, int y, int length)
{
	int i ;
	for (i = x ; i < x + length ; i++)
		set_value_at(i, y, 1) ;	
}

static int value_at(int x, int y)
{
	if (x < 0 || x > WIDTH - 1)
		return 1 ;
	if (y < 0 || y > HEIGHT - 1)
		return 1 ;
	return GRID[grid_y(y)][x] ;
}

static void set_value_at(int x, int y, int value)
{
	GRID[grid_y(y)][x] = value ;
}

static int grid_y(int y)
{
	return HEIGHT - y - 1 ;
}
