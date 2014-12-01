#ifndef I2C_H
#define I2C_H

void i2c_setup(void) ;

void i2c_read(void *buf, int count) ;

void i2c_write(void *buf, int count) ;

#endif
