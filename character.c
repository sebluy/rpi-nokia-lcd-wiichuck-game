#include <stdio.h>
#include <unistd.h>

#include "character.h"
#include "wii_chuck.h"
#include "world.h"

#define HEIGHT CHARACTER_HEIGHT
#define WIDTH CHARACTER_WIDTH
#define JUMP_VEL 2
#define GRAVITY 0.2

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
	.jump = 0,
	.grid = GRID
} ;

static wii_chuck_state *state ;

static void update_state(void) ;
static void update_jump(void) ;

static void update_vel(void) ;
static void update_vel_x(void) ;
static void update_vel_y(void) ;

static void update_pos(void) ;
static void update_pos_x(void) ;
static void update_pos_y(void) ;

static int grid_y(int y) ;

void character_update(void)
{
	world_remove_character(&c) ;
	update_state() ;
	world_add_character(&c) ;
}

int character_value_at(int x, int y)
{
	return c.grid[grid_y(y)][x] ;
}

static int grid_y(int y)
{
	return HEIGHT - y - 1 ;
}

static void update_state(void)
{
	state = wii_chuck_get_state() ;

	update_jump() ;
	update_vel() ;
	update_pos() ;
}

static void update_jump(void)
{
	if (c.vel_y == 0 && state->c_button)
		c.jump = 1 ;
	else
		c.jump = 0 ;
}

static void update_vel(void)
{
	update_vel_x() ;
	update_vel_y() ;
	world_character_limit_vel(&c) ;
}

static void update_pos(void)
{
	update_pos_x() ;
	update_pos_y() ;
}

static void update_vel_x(void)
{
	double x ;

	x = state->x_joystick - CENTER_JOYSTICK_X ;

	if (x > 0)
		c.vel_x = (RIGHTMOST_JOYSTICK_X - x)/RIGHT_JOYSTICK_X_RANGE ;
	else if (x < 0)
		c.vel_x = -(LEFTMOST_JOYSTICK_X - x)/LEFT_JOYSTICK_X_RANGE ;
	else
		c.vel_x = 0 ;
}

static void update_vel_y(void)
{
	if (c.jump)
		c.vel_y = JUMP_VEL ;
	else
		c.vel_y -= GRAVITY ;
}

static void update_pos_x(void)
{
	int move_left_ok ;
	int move_right_ok ;
	
	move_left_ok = c.vel_x < -0.5 ;
	move_right_ok = c.vel_x > 0.5 ;

	if (move_right_ok || move_left_ok)
		c.pos_x += c.vel_x ;

}

static void update_pos_y(void)
{
	c.pos_y += c.vel_y ;
}

