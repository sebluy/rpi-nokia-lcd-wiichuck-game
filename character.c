#include <stdio.h>
#include <unistd.h>

#include "character.h"
#include "wii_chuck.h"
#include "world.h"

#define HEIGHT CHARACTER_HEIGHT
#define WIDTH CHARACTER_WIDTH
#define JUMP_VEL 2
#define GRAVITY 0.01

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
	.vel_y = 0,
	.jump_time = 0,
	.jumping = 0,
	.grid = GRID
} ;

static void character_adjust_pos(void) ;

void character_update(void)
{
	world_remove_character(c) ;
	
	character_adjust_pos() ;

	world_add_character(c) ;
}

static void character_adjust_pos(void)
{
	double x ;
	
	wii_chuck_state *state ;

	state = wii_chuck_get_state() ;

	if (state->c_button && !c.jumping) {
		c.vel_y = JUMP_VEL ;
		c.jumping = 1 ;
		c.jump_time = 0 ;
	}

	x = state->x_joystick - CENTER_JOYSTICK_X ;

	if (x > 0)
		c.vel_x = (RIGHTMOST_JOYSTICK_X - x)/RIGHT_JOYSTICK_X_RANGE ;
	else if (x < 0)
		c.vel_x = -(LEFTMOST_JOYSTICK_X - x)/LEFT_JOYSTICK_X_RANGE ;
	else
		c.vel_x = 0 ;

	/* positioning */
	if (c.vel_x < -0.5 || c.vel_x > 0.5)
		c.pos_x += c.vel_x ;

	c.pos_y += c.vel_y ;

	if (c.jumping) {
		if (c.pos_y >= 0) {
			c.vel_y -= GRAVITY*(c.jump_time * c.jump_time) ;
			c.jump_time++ ;
		} else {
			c.pos_y = 0 ;
			c.vel_y = 0 ;
			c.jumping = 0 ;
		}
	}
	
	
}

