#ifndef CHARACTER_H
#define CHARACTER_H

#define CHARACTER_WIDTH 5
#define CHARACTER_HEIGHT 11

typedef struct {
	double pos_x ;
	double pos_y ;
	double vel_x ;
	unsigned char grid[CHARACTER_HEIGHT][CHARACTER_WIDTH] ;
} character ;

void character_update(void) ;

void character_set_pos(double x, double y) ;

#endif
