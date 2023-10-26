#include "funkcjep.h"
#include "funkcjes.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//producent
int main(int argc, char* argv[]){
	
	int infile;
	if((infile = open(argv[1], O_RDONLY, 0)) == -1){
		perror("OPEN ERROR");
		exit(EXIT_FAILURE);
	}

	sem_t *semaforkonsument = semOpen("/semaforkonsument");
    sem_t *semaforproducent = semOpen("/semaforproducent");
    
    printf("Producent przed sesja krytyczna. Wartosc semafora: %d\n", semInfo(semaforkonsument));
    int fdmem;
    fdmem = memOpen("/pamiec");
    SegmentPD *m_adrr;
	m_adrr = memMap(fdmem); // odwzorowanie pamieci dzielonej w wirtualnej przestrzeni adresowej procesu
	memSize(fdmem);
	
	char bufor[3];
	
	while(1){
		semP(semaforproducent);
	 printf("Producent w sesji krytycznej. Wartosc semafora: %d\n", semInfo(semaforkonsument));
	 
	 int a ;
	 a = read(infile, bufor, sizeof(bufor));
	 
	 if(a == -1){
	 	perror("READ ERROR");
	 	exit(EXIT_FAILURE);
	 }
	 
	 if(a == 0){
	m_adrr -> bufor[m_adrr -> wstaw][0] = '\0';
    m_adrr -> wstaw = (m_adrr -> wstaw + 1) % NBUF;
    semV(semaforkonsument);
    break;
	}
    
    printf("Producent:\n");
    if((write(STDOUT_FILENO, bufor, sizeof(bufor))) == -1){
            perror("WRITE ERROR");
            exit(EXIT_FAILURE);
	}
	 printf("\n");
    
    memcpy(m_adrr -> bufor[m_adrr -> wstaw], bufor, sizeof(bufor));
    m_adrr -> wstaw = (m_adrr -> wstaw + 1) % NBUF;
    
    semV(semaforkonsument);
    printf("Producent po sesji krytycznej. Wartosc semafora: %d\n", semInfo(semaforproducent));
    
	}
	
	semClose(semaforproducent);
	semClose(semaforkonsument);
	memUnmap(m_adrr);
	memClose(fdmem);
	memClose(infile);
	
	return 0;
}
