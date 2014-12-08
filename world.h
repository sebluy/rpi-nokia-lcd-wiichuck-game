#ifndef WORLD_H
#define WORLD_H

#include "character.h"
#include "lcd_display.h"

#define WORLD_WIDTH LCD_DISPLAY_WIDTH
#define WORLD_HEIGHT LCD_DISPLAY_HEIGHT

/* add character */
void world_add_character(character c) ;

/* remove character */
void world_remove_character(character c) ;

/* update the character in the world and then send to the display */
void world_update(void) ;

#endif
