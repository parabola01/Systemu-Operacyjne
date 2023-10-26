#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>
#include "funkcjep.h"
#include "funkcjes.h"

int memCreate(const char* name){
	int fd;
	if((fd = shm_open(name, O_RDWR|O_CREAT|O_EXCL, 0644))== -1){
		perror("SHM_OPEN ERROR");
		exit(EXIT_FAILURE);
	}
	
	return fd;
}

int memOpen(const char *name){
	int fd;
	if((fd = shm_open(name, O_RDWR, 0644)) == -1){
		perror("SHM_OPEN ERROR");
		exit(EXIT_FAILURE);
	}
	
	return fd;
}
void *memMap(int fd){
    SegmentPD *m_addr = (SegmentPD *) mmap(NULL, sizeof(SegmentPD), PROT_EXEC|PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(m_addr == MAP_FAILED){
        perror("MMAP ERROR");
        exit(EXIT_FAILURE);
    }
    return m_addr;
}

void memClose(int fd){
	if (close(fd) == -1){
        perror("CLOSE ERROR");
        exit(EXIT_FAILURE);
	}
}

void memUnmap(void *addr){
    if(munmap(addr, sizeof(SegmentPD)) == -1){
        perror("MUNMAP ERROR");
        exit(EXIT_FAILURE);
    }
}

void memSize(int fd){ // ustawia dlugosc obiektu pamieci dzielonej o deskryptorze fd
    if(ftruncate(fd, sizeof(SegmentPD)) == -1){ 
        perror("FTRUNCATE ERROR");
        exit(EXIT_FAILURE);
    }
    printf("Rozmiar pamieci dzielonej: %ld\n", sizeof(SegmentPD));
}

void memRemove(const char *name){
	if(shm_unlink("/pamiec") == -1){
        perror("SHM_UNLINK");
}
	else
	printf("Pamiec dzielona usunieta\n");
}



