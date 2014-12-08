#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#define LCD_WIDTH 84
#define LCD_HEIGHT 48

/* setup lcd for use */
void lcd_display_setup(void) ;

/* turn off all pixels */
void lcd_display_reset(void) ;

/* set a single pixel at (x, y) from top left */
void lcd_display_set(int x, int y) ;

/* clear a single pixel at (x, y) from top left */
void lcd_display_clear(int x, int y) ;

/* write data out to the lcd */
/* sets and clears will not display until updated */
void lcd_display_update(void) ;

#endif
