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

	if (c->pos_x >= WIDTH - CHARACTER_WIDTH - 1)
		c->clear_right = 0 ;
	else
		c->clear_right = 1 ;
}

void world_setup(void)
{
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
	int x, y, i, j ;
	x = c->pos_x ;
	y = HEIGHT - c->pos_y ;
	for (j = 0 ; j < CHARACTER_HEIGHT ; j++) {
		for (i = 0 ; i < CHARACTER_WIDTH ; i++) {
			if (add)
				GRID[y + j - CHARACTER_HEIGHT][x + i] = 
					c->grid[j][i] ;
			else
				GRID[y + j - CHARACTER_HEIGHT][x + i] = 0 ;
		}
	}
}
