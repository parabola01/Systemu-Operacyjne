#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
	int i=0;
	
	printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp()); // wypisywane identyfikatory procesu macierzystego
				
	for(i=0; i<3; i++)
	{
		int id = fork(); // tworzenie procesow potomnych
		switch (id) 
		{
			case -1: // porazka
				perror("fork error");
				exit(1);
				
				break;
			
			case 0: // akcja dla procesu potomnego
				sleep(1); // uspienie procesow potomnych
				printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp()); // wypisywane identyfikatory procesow
				
				break;
			
			default: // akcja dla procesu macierzystego
				sleep(2);
				
				break;
		};
	}
return 0;
}
