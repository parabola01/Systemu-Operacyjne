#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char *argv[]){
	
	if(argc != 3){
		printf("Nieprawidlowa liczba argumentow\n");
		exit(EXIT_FAILURE);
	}
	else{
	
	char *opcja=argv[1];
	int numer_sygnalu=atoi(argv[2]);
	
	int a = fork();
	
	switch(a)
	{
		case -1:
			perror("fork error");
			exit(EXIT_FAILURE);
			
		case 0:
			execl("./3a.x", "3a.x", argv[1] ,argv[2], NULL);
			perror("execl error");
			_exit(2);
			
		default: 
		
			if( kill(a,0) == ESRCH){
				perror("proces nie istnieje");
				exit(EXIT_FAILURE);
			}
			else{
			sleep(2);
			kill(a, numer_sygnalu);
			printf("Sygnal wyslany\n");}
			
	}
}
	
	return 0;
}
