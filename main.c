#include <unistd.h>
#include <stdio.h>

#include "lcd_display.h"
#include "wii_chuck.h"

int main(int argc, char *argv[])
{
	unsigned char STICK_MAN[][5] =
		{{0, 1, 1, 1, 0},
		 {0, 1, 0, 1, 0},
		 {0, 1, 1, 1, 0},
		 {0, 0, 1, 0, 0},
		 {1, 1, 1, 1, 1},
		 {0, 0, 1, 0, 0},
		 {0, 0, 1, 0, 0},
		 {0, 1, 1, 1, 0},
		 {0, 1, 0, 1, 0},
		 {0, 1, 0, 1, 0},
		 {1, 1, 0, 1, 1}} ;

	int x, y ;

	lcd_display_setup() ;
	lcd_display_reset() ;
	lcd_display_update() ;

	for (x = 0 ; x < 5 ; x++)
		for (y = 0 ; y < 11 ; y++)
			if (STICK_MAN[y][x]) 
				lcd_display_set(x, y) ;

	lcd_display_update() ;

	return 0 ;
}
