#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
	int i=0;
	
	printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp()); // wypisywane identyfikatory procesu maceirzystego
				
	for(i=0; i<3; i++)
	{
		switch (fork()) // tworzenie procesow potomnych
		{
			case -1: // porazka
				perror("fork error");
				exit(1);
				
				break;
			
			case 0: // akcja dla procesu potomnego
				setpgid(getpid(), 0);
				printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp()); // wypisywane identyfikatory procesow
				
				break;
			
			default: // akcja dla procesu macierzystego
				wait(0); // proces macierzysty czeka na wykonanie procesu potomnego
				
				break;
		};
	}
return 0;
}
