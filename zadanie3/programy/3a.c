#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

void obsluga (int numer_sygnalu)
{
	printf("Zostal przechwycony sygnal nr: %d\n", numer_sygnalu);
}

int main (int argc, char *argv[]){
	
	char *nazwa=argv[0];
	char *opcja=argv[1];
	int numer_sygnalu=atoi(argv[2]);
	
	if(argc !=3){
		printf("Nieprawidlowa liczba argumentow\n");
		exit(EXIT_FAILURE);
	}
	else{
	if(strcmp (opcja, "d")==0){
		if(signal(numer_sygnalu, SIG_DFL) != SIG_ERR){
			printf("Wykonana operacja domyslna\n");
			pause();
			exit(EXIT_SUCCESS);}
		else{
			perror("error");
			exit(EXIT_FAILURE);
		}
	}

	else if(strcmp (opcja, "i")==0){
		
		if(signal(numer_sygnalu, SIG_IGN) != SIG_ERR){
			printf("Wykonana operacja ignorowania\n");
			pause();
			exit(EXIT_SUCCESS);}
		else{
			perror("error");
			exit(EXIT_FAILURE);
		}
	}

	else if(strcmp (opcja, "o")==0){
		
		if(signal(numer_sygnalu, obsluga) != SIG_ERR){
			obsluga(numer_sygnalu);
			pause();
			exit(EXIT_SUCCESS);}
		else{
			perror("error");
			exit(EXIT_FAILURE);
		}
	}
	
	else{
		printf("Wprowadzona nieprawidlowa opcje obslugi\n");
		exit(EXIT_FAILURE);
	}
}
	return 0;
	
}
