#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char *argv[]){
	int i,j,c,status;
	char *opcja=argv[1];
	int numer_sygnalu=atoi(argv[2]);
	
	int a = fork();
	
		switch(a)
	{
		case -1:
			perror("fork error");
			exit(EXIT_FAILURE);
			
		case 0:
			c = setpgid(getpid(), 0);
			signal(atoi(opcja), SIG_IGN);
			
			for(i=0; i<3; i++){
			
			
			switch(fork()){
				case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
				
				case 0:
				execl("./3a.x", "3a.x", argv[1] ,argv[2], NULL);
				perror("execl error");
				_exit(2);
				
				default:
				if(i ==2){
				wait(&status);
				wait(&status);
				wait(&status);	
				printf("Status zakonczenia procesu: %x\n", status);}	
			}
}
		default: 
		sleep(1);
		j = getpgid(a);
			if( kill(j,0) == ESRCH){
				perror("proces nie istnieje");
				exit(EXIT_FAILURE);}
			else {
				kill(-j, numer_sygnalu);
				printf("Wyslano sygnal nr: %d do grupy procesow o identyfikatorze: %d\n", numer_sygnalu, setpgid(getpid(),0));
			} 
		}
	
	return 0;
	
}
