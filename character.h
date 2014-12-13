#ifndef CHARACTER_H
#define CHARACTER_H

#define CHARACTER_WIDTH 5
#define CHARACTER_HEIGHT 11

typedef struct {
	double pos_x ;
	double pos_y ;
	int i_pos_x ;
	int i_pos_y ;
	double vel_x ;
	double vel_y ;
	int jump ;
	unsigned char grid[CHARACTER_HEIGHT][CHARACTER_WIDTH] ;
} character ;

void character_update(void) ;

int character_value_at(int x, int y) ;

#endif
