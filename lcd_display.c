#include <unistd.h>
#include <string.h>

#include "gpio.h"
#include "spi.h"
#include "lcd_display.h"

#define DC  "23"
#define SCE "24"
#define RST "25"

static unsigned char byte_grid[LCD_HEIGHT/8][LCD_WIDTH] ;

/* intitialization commands taken from sparkfun website */
static unsigned char commands[6] =
	{0x21,   /* enable extended commands */
	 0xB0,   /* set lcd vop (contrast) */
	 0x04,   /* set temp coefficent */
	 0x14,   /* lcd bias mode 1:48 */
	 0x20,   /* prepare for modifying display control mode */
	 0x0C} ; /* set display control, normal mode */

void lcd_display_setup(void)
{
	gpio_setup(DC) ;
	gpio_setup(SCE) ;
	gpio_setup(RST) ;

	gpio_set_value(DC, "0") ;
	gpio_set_value(SCE, "0") ;
	gpio_set_value(RST, "1") ;
	
	usleep(5e-3) ;

	gpio_set_value(RST, "0") ;
	gpio_set_value(RST, "1") ;

	spi_setup() ;
	spi_write(commands, sizeof(commands)) ;

	gpio_set_value(DC, "1") ;
}

void lcd_display_reset(void)
{
	memset(byte_grid, 0, sizeof(byte_grid)) ;
}

void lcd_display_set(int x, int y)
{
	int byte_grid_y ;
	unsigned char bit ;
	byte_grid_y = y / 8 ;
	bit = 1 << (y % 8) ;
	byte_grid[byte_grid_y][x] |= bit ;
}

void lcd_display_clear(int x, int y)
{
	int byte_grid_y ;
	unsigned char bit ;
	byte_grid_y = y / 8 ;
	bit = 1 << (y % 8) ;
	byte_grid[byte_grid_y][x] &= ~bit ;
}

void lcd_display_update(void)
{
	spi_write(byte_grid, sizeof(byte_grid)) ;
	
}

