#include <unistd.h>

#include "character.h"
#include "lcd_display.h"
#include "world.h"

#define WIDTH WORLD_WIDTH
#define HEIGHT WORLD_HEIGHT

#define ADD 1
#define REMOVE 0

static unsigned char GRID[HEIGHT][WIDTH] ;
static void change_character(character c, int add) ;

void world_add_character(character c)
{		
	change_character(c, ADD) ;
}

void world_remove_character(character c)
{
	change_character(c, REMOVE) ;
}

void world_update(void)
{
	usleep(16666) ; /* 60 Hz */
	character_update() ;
	lcd_display_map(GRID) ;
	lcd_display_update() ;
}

static void change_character(character c, int add)
{
	int x, y, i, j ;
	x = c.pos_x ;
	y = HEIGHT - c.pos_y ;
	for (j = 0 ; j < CHARACTER_HEIGHT ; j++) {
		for (i = 0 ; i < CHARACTER_WIDTH ; i++) {
			if (add)
				GRID[y + j - CHARACTER_HEIGHT][x + i] = 
					c.grid[j][i] ;
			else
				GRID[y + j - CHARACTER_HEIGHT][x + i] = 0 ;
		}
	}
}
