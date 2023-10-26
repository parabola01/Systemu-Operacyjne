#include "funkcjes.h"
#include "funkcjep.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>

void finish(void){
	semRemove("/semaforproducent");
	semRemove("/semaforkonsument");
	memRemove("/pamiec");
	printf("Koniec!\n");
}

int main(int argc, char* argv[]){
	
	if (argc != 5){
        printf("Podano nieprawidlowa ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }
    
    if (atexit(finish) != 0){
    	perror("ATEXIT ERROR");
    	exit(EXIT_FAILURE);
	}
	
	semCreate("/semaforproducent", NBUF); // tworze semafor dla producenta
	sem_t *s1 = semOpen("/semaforproducent");
	printf("Wartosc semafora: %d\n",semInfo(s1));
	printf("Adres semafora: %p\n", (void *)s1);
	
	semCreate("/semaforkonsument", 0); // tworze semafor dla konsumenta
	sem_t *s2 = semOpen("/semaforkonsument");
	printf("Wartosc semafora: %d\n",semInfo(s2));
	printf("Adres semafora: %p\n", (void *)s2);
	
	memCreate("/pamiec");
	int memfd;
	memfd = memOpen("/pamiec");
	printf("Pamiec dzielona utworzona\n");
	printf("Deskryptor pamieci dzielonej: %d\n", memfd);
	memSize(memfd);
	
	SegmentPD *m_addr;
	m_addr = memMap(memfd); // ustawia dlugosc obiektu pamieci dzielonej o deskryptorze fd
	
	m_addr->wstaw = 0;
    m_addr->wyjmij = 0;
    
    for (int i = 0; i < 2; i++)
    {

        switch (fork())
        {
        case -1:
            perror("fork error");
            exit(2);
        case 0:
            // Uruchomienie producenta
            if (i == 0)
            {
                execl(argv[1], argv[1], argv[3], NULL);
                perror("execl error");
                _exit(2);
            }

            // Uruchomienie konsumenta
            if (i == 1)
            {
                execl(argv[2], argv[2], argv[4], NULL);
                perror("execl error");
                _exit(2);
            }
        }
    }
    
    wait(NULL);
    wait(NULL);

	semClose(s1);
	semClose(s2);
    memUnmap(m_addr);
    memClose(memfd);

	
	if(signal(SIGINT, my_handler) == SIG_ERR){
        perror("SIGNAL ERROR");
        exit(EXIT_FAILURE);
    }
	
	return 0;
}
