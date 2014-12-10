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
	.clear_top = 1,
	.clear_bottom = 0,
	.clear_right = 1,
	.clear_left = 0,
	.grid = GRID
} ;

static wii_chuck_state *state ;

static void update_state(void) ;

static void update_clearances(void) ;

static void update_jump(void) ;

static void update_vel(void) ;
static void update_vel_x(void) ;
static void update_vel_y(void) ;

static void update_pos(void) ;
static void update_pos_x(void) ;
static void update_pos_y(void) ;

void character_update(void)
{
	world_remove_character(&c) ;
	update_state() ;
	world_add_character(&c) ;
}

static void update_state(void)
{
	state = wii_chuck_get_state() ;

	update_clearances() ;
	update_jump() ;
	update_vel() ;
	update_pos() ;
}

static void update_clearances(void)
{
	world_character_clearances(&c) ;
}

static void update_jump(void)
{
	if (c.clear_bottom)
		c.jump = 0 ;
	else if (state->c_button)
		c.jump = 1 ;
}

static void update_vel(void)
{
	update_vel_x() ;
	update_vel_y() ;
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
	if (c.clear_bottom)
		c.vel_y -= GRAVITY ;
	else if (c.jump)
		c.vel_y = JUMP_VEL ;
	else
		c.vel_y = 0 ;
}

static void update_pos_x(void)
{
	int move_left_ok ;
	int move_right_ok ;
	
	move_left_ok = c.vel_x < -0.5 && c.clear_left ;
	move_right_ok = c.vel_x > 0.5 && c.clear_right ;

	if (move_right_ok || move_left_ok)
		c.pos_x += c.vel_x ;

}

static void update_pos_y(void)
{
	int move_down_ok ;
	int move_up_ok ;

	move_down_ok = c.vel_y < 0 && c.clear_bottom ;
	move_up_ok = c.vel_y > 0 && c.clear_top ;

	if (move_up_ok || move_down_ok)
		c.pos_y += c.vel_y ;
}

