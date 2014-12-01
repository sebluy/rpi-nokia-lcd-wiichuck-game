#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

static void error(int fd) ;
static void open_error(char *filename) ;
static void get_filename(int fd, char filename[80]) ;

int Open(char *filename, int flags)
{
	int fd ;
	if ((fd = open(filename, flags)) < 0 )
		open_error(filename) ;
	return fd ;
}

void Write(int fd, void *buf, int count)
{
	if (write(fd, buf, count) < count)
		error(fd) ;
}

void Read(int fd, void *buf, int count)
{
	if (read(fd, buf, count) < count)
		error(fd) ;
}

void Ioctl(int fd, int request, void *argp)
{
	if (ioctl(fd, request, argp) < 0)
		error(fd) ;
}

void Close(int fd)
{
	if (close(fd) < 0)
		error(fd) ;
}

static void open_error(char *filename)
{
	perror(filename) ;
	exit(0) ;	
}

static void error(int fd)
{
	char filename[80] ;
	get_filename(fd, filename) ;
	perror(filename) ;
	exit(0) ;
}

static void get_filename(int fd, char filename[80])
{
	char path[80] ;
	sprintf(path, "/proc/self/fd/%d", fd) ;
	readlink(path, filename, 80) ;
}
