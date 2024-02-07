//*****************************************************************************
//  Turaco-DOS
//
//  include/syscall.h
//*****************************************************************************

#pragma once

// File exists
#define F_OK 0b00000001

// File can be read
#define R_OK 0b00000010

// File can be written
#define W_OK 0b00000100

// File can be executed
#define X_OK 0b00001000

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtypedef-redefinition"
typedef unsigned long int size_t;
typedef long int ssize_t;
typedef long long int off_t;
typedef unsigned long int intptr_t;
#pragma clang diagnostic pop

int access(const char *path, int amode);

int chdir(const char *);

int close(int);

int dup(int);

int dup2(int, int);

int fchdir(int);

int fsync(int);

int ftruncate(int, off_t);

char *getcwd(char *, size_t);

off_t lseek(int, off_t, int);

ssize_t read(int, void *, size_t);

int rmdir(const char *);

unsigned sleep(unsigned);

void sync(void);

int unlink(const char *);

ssize_t write(int, const void *, size_t);
