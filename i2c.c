#include <linux/i2c-dev.h>

#include "i2c.h"
#include "file.h"

#define WII_CHUCK_SLAVE_ADDRESS 0x52

static int fd ;

void i2c_setup(void)
{
	fd = Open("/dev/i2c-1", O_RDWR) ;
	Ioctl(fd, I2C_SLAVE, (void*)WII_CHUCK_SLAVE_ADDRESS) ;
}

void i2c_read(void *buf, int count)
{
	Read(fd, buf, count) ;
}

void i2c_write(void *buf, int count)
{
	Write(fd, buf, count) ;
}
