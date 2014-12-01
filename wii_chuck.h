#ifndef WII_CHUCK_H
#define WII_CHUCK_H

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
