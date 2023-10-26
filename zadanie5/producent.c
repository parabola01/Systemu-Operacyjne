#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#define LIMIT 6

int main(int argc, char *argv[]){
	
	char znak[LIMIT+1];
    
    int fd = open("potok", O_WRONLY); // deskryptor potoku
    int plik = open(argv[1], O_RDONLY); // deskryptor tekst1
    
    srand(time(0));
    
    printf("Jestem producentem, czytam dane z pliku\n");
    
    int nbytes;
    while((nbytes = read(plik, znak,sizeof(znak)))>0){
			sleep(rand()%5);
		if(write(fd, znak, nbytes)==-1){
			perror("write error");
			return 1;
		}
		printf("Producent pobral z pliku: %s \n",znak);
		sleep(1);
		memset(znak, 0, 6);
	}
	
	close(plik);
	close(fd);
	return 0;
	
}
