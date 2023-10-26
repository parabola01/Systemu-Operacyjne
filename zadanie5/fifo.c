#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

void koniec();

int main(int argc, char *argv[]){
	
	if(argc!=3){ 
        perror("Nieprawidlowa liczba argumentow\n");
        exit(EXIT_FAILURE);
    }
    
    if(atexit(koniec) != 0){
        perror("atexit error\n");
        exit(EXIT_FAILURE);
    }
    
    if(mkfifo("potok", 0777) == -1){
        perror("mkfifo error");
        _exit(EXIT_FAILURE);
    }
    
    int a = fork();
	if(a == -1){
		perror("fork error");
		exit(EXIT_FAILURE);
		exit(1);
	}
	else if(a == 0){
		execl("./producent.x","producent",argv[1],argv[2],"potok", NULL);
        perror("execl producent error"); 
        _exit(EXIT_FAILURE);	
	}
	
    int b = fork();
    if(b == -1){
    	perror("fork error");
		exit(EXIT_FAILURE);
		exit(1);
	}
	else if(b == 0){
		execl("./konsument.x","konsument",argv[1],argv[2],"potok", NULL);
        perror("execl konsument error"); 
        _exit(EXIT_FAILURE);
	}
	
	wait(NULL);
	wait(NULL);
	
	return 0;
    
}

void koniec(){
    if(unlink("potok") == -1){ 
        perror("unlink error");
        _exit(EXIT_FAILURE); 
    } 
    printf("Potok usuniety\n");
}
