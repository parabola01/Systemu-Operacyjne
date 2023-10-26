#include <sys/stat.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include "funkcjes.h"

void semCreate(const char *name, int val){ // tworzenie semafora z wartoscia poczatkowa val
	if((sem_open(name, O_CREAT|O_EXCL, 0777, val)) == SEM_FAILED){
		perror("SEM_OPEN ERROR");
		exit(EXIT_FAILURE);
	}
	else{
		printf("Semafor utworzony z nazwa: %s i wartoscia: %d\n", name, val);
	}
}

void semRemove(const char *name){ // usuwanie semafora
	if(sem_unlink(name) == -1){
		perror("SEM_UNLINK ERROR");
		exit(EXIT_FAILURE);
	}
	else{
		printf("Semafor usuniety\n");
	}
}

sem_t *semOpen(const char *name){ // dostep do istniejacego semafora
	sem_t *semaphore;
	if((semaphore = sem_open(name,0)) == SEM_FAILED){
		perror("SEM_OPEN ERROR");
		exit(EXIT_FAILURE);
	}
	return semaphore;
}

void semClose(sem_t *semaphore){ // zamkniecie semafora
	if(sem_close(semaphore) == -1){
        perror("SEM_CLOSE ERROR");
        exit(EXIT_FAILURE);
	}
	else{
		printf("Semafor zamkniety\n");
	}
}

void semV(sem_t *semaphore){ // podniesienie semafora
	if(sem_post(semaphore) == -1){
		perror("SEM_POST ERROR");
		exit(EXIT_FAILURE);
	}
	else{
		printf("Semafor podniesiony\n");
	}
}

void semP(sem_t *semaphore){ // opuszczenie semafora
	if(sem_wait(semaphore) == -1){
		perror("SEM_WAIT ERROR");
		exit(EXIT_FAILURE);
	}
	else{
		printf("Semafor opuszczony\n");
	}
}

int semInfo(sem_t *semaphore){ // informacja o wartosci semafora
	int val;
	if(sem_getvalue(semaphore, &val) == -1){
        perror("SEM_GET_VALUE ERROR");
        exit(EXIT_FAILURE);
	}
	
	return val;
}

void my_handler(int sig){
        exit(EXIT_FAILURE);
}
