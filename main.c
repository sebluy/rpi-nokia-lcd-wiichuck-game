#include <unistd.h>
#include <stdio.h>

#include "lcd_display.h"
#include "wii_chuck.h"

int main(int argc, char *argv[])
{

	wii_chuck_state *wii_chuck ;

	lcd_display_setup() ;
	lcd_display_map() ;

	wii_chuck_setup() ;

	while (1) {
		wii_chuck = wii_chuck_get_state() ;

		while (!wii_chuck->c_button ) {
			usleep(16667) ;
			wii_chuck = wii_chuck_get_state() ;
		}

		printf("Z button: %x\n", wii_chuck->z_button) ;
		printf("C button: %x\n", wii_chuck->c_button) ;
		printf("X joystick: %x\n", wii_chuck->x_joystick) ;
		printf("Y joystick: %x\n", wii_chuck->y_joystick) ;
		printf("X acceleration : %x\n", wii_chuck->x_accel) ;
		printf("Y acceleration : %x\n", wii_chuck->y_accel) ;
		printf("Z acceleration : %x\n", wii_chuck->z_accel) ;

		while (wii_chuck->c_button ) {
			usleep(16667) ;
			wii_chuck = wii_chuck_get_state() ;
		}
	}

	return 0 ;
}
