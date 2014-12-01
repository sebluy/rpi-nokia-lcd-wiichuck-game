#include <unistd.h>

#include "i2c.h"
#include "wii_chuck.h"

#define DATA_LENGTH 6
#define DELAY 240 /* (6 bytes * 8 bits ) / 200 KHz = 240 us */

static unsigned char receive_data[DATA_LENGTH] ;

static wii_chuck_state wii_chuck ;

static void request(void) ;
static void recieve(void) ;
static void decode(void) ;
static void load_state(void) ;

void wii_chuck_setup(void)
{
	unsigned char init_cmds[] = {0x40, 0x00} ;
	i2c_setup() ;
	i2c_write(init_cmds, sizeof(init_cmds)) ;
	usleep(DELAY) ;
}

wii_chuck_state *wii_chuck_get_state(void)
{
	request() ;
	usleep(DELAY) ;
	recieve() ;
	decode() ;
	load_state() ;

	return &wii_chuck ;
}

static void request(void)
{
	unsigned char zero ;
	zero = 0 ;
	i2c_write(&zero, 1) ;
}

static void recieve(void)
{
	i2c_read(receive_data, DATA_LENGTH) ;
}

static void decode(void)
{
	int i ;
	for (i = 0 ; i < DATA_LENGTH ; i++) {
		receive_data[i] = (receive_data[i] ^ 0x17) + 0x17 ;
	}
}

static void load_state(void)
{
	wii_chuck.z_button = !(receive_data[5] & 0x1) ;
	wii_chuck.c_button = !(receive_data[5] & 0x2) ;

	wii_chuck.x_joystick = receive_data[0] ;
	wii_chuck.y_joystick = receive_data[1] ;

	wii_chuck.x_accel = receive_data[2] + ((receive_data[5] >> 2) & 0x3) ;
	wii_chuck.y_accel = receive_data[3] + ((receive_data[5] >> 4) & 0x3) ;
	wii_chuck.z_accel = receive_data[4] + ((receive_data[5] >> 6) & 0x3) ;
}
