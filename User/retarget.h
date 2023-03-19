#ifndef _RETARGET_H
#define _RETARGET_H

#include <sys/stat.h>
#include <stdio.h>

int _isatty(int fd);

int _write(int fd, char *ptr, int len);

int _close(int fd);

int _lseek(int fd, int ptr, int dir);

int _read(int fd, char *ptr, int len);

int _fstat(int fd, struct stat *st);


#endif //_RETARGET_H
