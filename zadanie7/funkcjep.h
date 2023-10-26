#ifndef FUNKCJEP
#define FUNKCJEP

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <unistd.h>

#define NBUF 2
#define NELE 7

typedef struct
{
    char bufor[NBUF][NELE];
    int wstaw, wyjmij;
} SegmentPD;

int memCreate(const char* name);

int memOpen(const char *name);

void *memMap(int fd);

void memClose(int fd);

void memUnmap(void *addr);

void memSize(int fd);

void memRemove(const char *name);


#endif
