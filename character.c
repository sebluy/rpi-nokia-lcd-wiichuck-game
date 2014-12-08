#include <stdio.h>

#include "character.h"
#include "world.h"

#define HEIGHT CHARACTER_HEIGHT
#define WIDTH CHARACTER_WIDTH

#define GRID \
	{{0, 1, 1, 1, 0}, \
	 {0, 1, 0, 1, 0}, \
	 {0, 1, 1, 1, 0}, \
	 {0, 0, 1, 0, 0}, \
	 {1, 1, 1, 1, 1}, \
	 {0, 0, 1, 0, 0}, \
	 {0, 0, 1, 0, 0}, \
	 {0, 1, 1, 1, 0}, \
	 {0, 1, 0, 1, 0}, \
	 {0, 1, 0, 1, 0}, \
	 {1, 1, 0, 1, 1}} \

static character c = { 
	.pos_x = 0,
	.pos_y = 0,
	.vel_x = 0,
	.grid = GRID
} ;

void character_update(void)
{
	world_remove_character(c) ;
	
	if (c.pos_x == 0)
		c.vel_x = 0.10 ;
	else if (c.pos_x == WORLD_WIDTH - 1)
		c.vel_x = -0.10 ;

	character_set_pos(c.pos_x + c.vel_x, c.pos_y) ;
	world_add_character(c) ;
}

void character_set_pos(double x, double y)
{
	c.pos_x = x ;
	c.pos_y = y ;
}

