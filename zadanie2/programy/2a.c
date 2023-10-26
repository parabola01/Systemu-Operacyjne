#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char * argv[]){
	int i=0;
	
	printf("UID: %d, GID: %d, PID: %d, PPID: %d, PGID: %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
		
	for(i=0; i<3; i++)
	{
		switch (fork()) // tworzenie procesow potomnych
		{
			case -1: // porazka
				perror("fork error"); // obsluga bledow
				exit(1);
				
				break;
			
			case 0: // akcja dla procesu potomnego
				execl(argv[1], argv[1], NULL); // uruchamianie programu "2b"
				perror("execl error"); // obsluga bledow
				_exit(2); 
				
				break;
			
			default: // akcja dla procesu macierzystego
				wait(0); // proces macierzysty czeka na wykonanie procesu potomnego
				
				break;
		};
	}
	
return 0;
}
