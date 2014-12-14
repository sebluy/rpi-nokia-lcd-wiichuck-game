#ifndef WORLD_H
#define WORLD_H

#include "character.h"
#include "lcd_display.h"

#define WORLD_WIDTH LCD_DISPLAY_WIDTH
#define WORLD_HEIGHT LCD_DISPLAY_HEIGHT

/* add character */
void world_add_character(character *c) ;

/* remove character */
void world_remove_character(character *c) ;

/* limits velocities due to collisions with objects */
void world_character_limit_vel(character *c) ;

/* returns 1 if character if there is something directly under character */
int world_character_grounded(character *c) ;

/* setup world and its dependencies */
void world_setup(void) ;

/* update the character in the world and then send to the display */
void world_update(void) ;

#endif
