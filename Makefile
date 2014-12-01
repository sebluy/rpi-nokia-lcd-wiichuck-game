CC = gcc
CFLAGS = -g -Wall
SRCS = lcd_display.c gpio.c file.c spi.c i2c.c wii_chuck.c main.c
OBJS := $(SRCS:.c=.o)
MAIN = main

all: $(MAIN)

###

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	rm -f *~ *.o *.d $(MAIN)

depend: $(SRCS)
	makedepend $^
