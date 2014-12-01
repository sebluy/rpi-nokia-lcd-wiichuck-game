#ifndef FILE_H
#define FILE_H

#include <fcntl.h>

/* open a file and exit with message if failure */
int Open(char *filename, int flags) ;

/* write a file and exit with message if failure */
void Write(int fd, void *buf, int count) ;

/* read a file and exit with message if failure */
void Read(int fd, void *buf, int count) ;

/* send a ioctl request and exit with message if failure */
void Ioctl(int fd, int request, void *argp) ;

/* close a file and exit with message if failure */
void Close(int fd) ;

#endif
