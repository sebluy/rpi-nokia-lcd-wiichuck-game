#include "i2c.h"
#include "wii_chuck.h"

#define DATA_LENGTH 6

static unsigned char receive_data[DATA_LENGTH] ;

static void request(void) ;
static void recieve(void) ;
static void decode(void) ;

void wii_chuck_init(void)
{
	unsigned char init_cmds[] = [0x40, 0x00] ;
	i2c_setup() ;
	i2c_write(init_cmds, sizeof(init_cmds)) ;
}

unsigned char *wii_chuck_get_data(void)
{
	request() ;
	recieve() ;
	decode() ;
	return receive_data ;
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

