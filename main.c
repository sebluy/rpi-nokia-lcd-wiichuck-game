#include <unistd.h>
#include <stdio.h>

#include "lcd_display.h"
#include "wii_chuck.h"
#include "world.h"

int main(int argc, char *argv[])
{
	world_setup() ;

	while (1)
		world_update() ;

	return 0 ;
}
