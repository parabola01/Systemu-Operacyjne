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
	
	int fd = open("potok", O_RDONLY); // deskryptoor potoku nazwanego
	int plik = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0666); // deskryptor tekst2
	
	srand(time(0));
	
	printf("Jestem konsumentem, zapisuje dane do pliku\n");
	
	int nbytes;
	sleep(1);
		while((nbytes = read(fd, znak,sizeof(znak)))>0){
			sleep(rand()%5);
		if(write(plik, znak, nbytes)==-1){
			perror("write error");
			return 1;
		}
		printf("Konsument umieszcza w pliku: %s \n",znak);
		memset(znak, 0, 6);
	}
	
	close(plik);
	close(fd);
	return 0;
}
