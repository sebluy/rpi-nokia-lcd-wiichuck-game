CC = gcc
CFLAGS = -g -Wall
SRCS = gpio.c file.c spi.c i2c.c wii_chuck.c lcd_display.c world.c character.c \
	main.c
OBJS := $(SRCS:.c=.o)
MAIN = main

all: $(MAIN)

###

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	rm -f *~ *.o $(MAIN)
