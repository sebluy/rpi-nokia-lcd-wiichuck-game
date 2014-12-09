#ifndef WII_CHUCK_H
#define WII_CHUCK_H

/* found expirementally */
#define RIGHTMOST_JOYSTICK_X 232
#define CENTER_JOYSTICK_X 128
#define LEFTMOST_JOYSTICK_X 31
#define RIGHT_JOYSTICK_X_RANGE (RIGHTMOST_JOYSTICK_X - CENTER_JOYSTICK_X)
#define LEFT_JOYSTICK_X_RANGE (CENTER_JOYSTICK_X - LEFTMOST_JOYSTICK_X)

typedef struct {
	int z_button ;
	int c_button ;
	int x_joystick ;
	int y_joystick ;
	int x_accel ;
	int y_accel ;
	int z_accel ;
} wii_chuck_state ;

void wii_chuck_setup(void) ;

wii_chuck_state *wii_chuck_get_state(void) ;

#endif
