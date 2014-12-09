#include <unistd.h>
#include <stdio.h>

#include "lcd_display.h"
#include "wii_chuck.h"
#include "world.h"

int main(int argc, char *argv[])
{
	wii_chuck_setup() ;
	lcd_display_setup() ;
	lcd_display_clear() ;
	lcd_display_update() ; 

	while (1) {
		world_update() ;
		lcd_display_update() ;
	}

	return 0 ;
}
