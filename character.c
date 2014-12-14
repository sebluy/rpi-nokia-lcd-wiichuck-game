#include "character.h"
#include "wii_chuck.h"
#include "world.h"

#define HEIGHT CHARACTER_HEIGHT
#define WIDTH CHARACTER_WIDTH
#define JUMP_VEL 2
#define RUN_VEL 0.5
#define GRAVITY 0.1

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
	.i_pos_x = 0,
	.i_pos_y = 0,
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

static int round_to_int(double d) ;

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
	if (world_character_grounded(&c) && state->c_button)
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
	c.i_pos_x = round_to_int(c.pos_x) ;
	c.i_pos_y = round_to_int(c.pos_y) ;
}

static void update_vel_x(void)
{
	double x ;

	x = state->x_joystick - CENTER_JOYSTICK_X ;

	if (x > 0)
		c.vel_x = RUN_VEL * x / RIGHT_JOYSTICK_X_RANGE ;
	else if (x < 0)
		c.vel_x = RUN_VEL * x / LEFT_JOYSTICK_X_RANGE ;
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
	c.pos_x += c.vel_x ;

}

static void update_pos_y(void)
{
	c.pos_y += c.vel_y ;
}

static int round_to_int(double d)
{
	return d > 0.0 ? d + 0.5 : d - 0.5 ;
}
