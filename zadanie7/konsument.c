#include "funkcjep.h"
#include "funkcjes.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <string.h>
//konsument
int main(int argc, char* argv[]){
	int outfile;
	if((outfile = open(argv[1], O_WRONLY, 0644)) == -1){
		perror("OPEN ERROR");
		exit(EXIT_FAILURE);
	}
	printf("jestem w konsumencie\n");
	sem_t *semaforkonsument = semOpen("/semaforkonsument");
    sem_t *semaforproducent = semOpen("/semaforproducent");
    
    printf("Konsument przed sesja krytyczna. Wartosc semafora: %d\n", semInfo(semaforkonsument));
    int fdmem;
    fdmem = memOpen("/pamiec");
    SegmentPD *m_adrr;
	m_adrr = memMap(fdmem);
	memSize(fdmem);
	
	char bufor[3];
    while(1){
    	semP(semaforkonsument);
    printf("Konsument w sesji krytycznej. Wartosc semafora: %d\n", semInfo(semaforkonsument));
    
    if(m_adrr -> bufor[m_adrr -> wyjmij][0] == '\0'){
            semV(semaforproducent);
            break;
        }
        
    memcpy(bufor, m_adrr -> bufor[m_adrr -> wyjmij], sizeof(bufor));
    m_adrr -> wyjmij = (m_adrr -> wyjmij + 1) % NBUF;
    
    if(write(outfile, bufor, sizeof(bufor)) == -1){
            perror("WRITE ERROR");
            exit(EXIT_FAILURE);
        }
   	sleep(2);
    printf("Konsument:\n");
    write(STDOUT_FILENO, bufor, sizeof(bufor));
    printf("\n");
     
    semV(semaforproducent);
    printf("Konsument po sesji krytycznej. Wartosc semafora: %d\n", semInfo(semaforkonsument));
	}
	
	semClose(semaforproducent);
	semClose(semaforkonsument);
	memUnmap(m_adrr);
	memClose(fdmem);
	memClose(outfile);
	
	return 0;
}
