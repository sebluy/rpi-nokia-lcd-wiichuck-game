#include <unistd.h>

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
/*static int value_at(int x, int y) ;*/
static void set_value_at(int x, int y, int value) ;

void world_add_character(character *c)
{		
	change_character(c, ADD) ;
}

void world_remove_character(character *c)
{
	change_character(c, REMOVE) ;
}

void world_character_clearances(character *c)
{
	if (c->pos_y <= 0)
		c->clear_bottom = 0 ;
	else
		c->clear_bottom = 1 ;
	
	if (c->pos_x <= 0)
		c->clear_left = 0 ;
	else
		c->clear_left = 1 ;
int
	if (c->pos_x >= WIDTH - CHARACTER_WIDTH - 1)
		c->clear_right = 0 ;
	else
		c->clear_right = 1 ;
}

void world_setup(void)
{
	add_platform(5, 5, 5) ;
	add_platform(10, 10, 5) ;
	add_platform(15, 15, 5) ;
	add_platform(20, 20, 5) ;
	add_platform(25, 25, 5) ;
	add_platform(30, 30, 5) ;
	add_platform(35, 35, 5) ;
	add_platform(40, 40, 5) ;

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
			set_value_at(c->pos_x + i, c->pos_y + j, value) ;
		}
	}
}

static void add_platform(int x, int y, int length)
{
	int i ;
	for (i = x ; i < x + length ; i++)
		set_value_at(i, y, 1) ;	
}

/*static int value_at(int x, int y)
{
	return GRID[grid_y(y)][x] ;
}*/

static void set_value_at(int x, int y, int value)
{
	GRID[grid_y(y)][x] = value ;
}

static int grid_y(int y)
{
	return HEIGHT - y - 1 ;
}
