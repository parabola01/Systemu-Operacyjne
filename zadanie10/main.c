#define _REENTRANT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#define CYKL 3 // liczba sekcji krytycznych
#define WATEK 5 // liczba watkow

int licznik = 0;
int num_tab[WATEK];
int wybor_tab[WATEK];

void unlock(int arg){
    num_tab[arg] = 0;
}

void lock(int arg){
	int max = 0;
    int i;
    wybor_tab[arg]=1;
    
	for(i = 0; i<WATEK; i++){
		num_tab[i]=0;
	}
	
    for(i = 0; i<WATEK; i++){
        int num = num_tab[i];
        if(num > max){
            max = num;
        }
	}

	num_tab[arg] = max + 1;
	wybor_tab[arg] = 0;
	
    for(i = 0; i <WATEK; i++){
        while(wybor_tab[i]) {}

        while(num_tab[i] !=0 && ((num_tab[i]<num_tab[arg]) || (num_tab[i]==num_tab[arg]&&i<arg))) {}
    }
}

void *watki(void *arg){
    srand(time(NULL));
    int rng = 2 + rand() % 3;

    int a = *(int*)arg;

    sleep(1);

    int i=0;
    int zmienna = a+CYKL+WATEK;
    while(i<CYKL){
        printf("\033[%d;%dH\033[2K", zmienna, 1);

        printf("Watek nr:%d w sekcji nr:%d\n", a+1,i+1);

        sleep(rng);
        
        lock(a);

        printf("\033[%d;%dH\033[2K", zmienna, 1);
        printf("\033[%d;%dH",zmienna, 55);
        printf("Watek nr:%d w sekcji nr:%d\n ", a+1,i+1);
	
        int num = licznik;
        num++;
        licznik = num;

        printf("\033[%d;%dH\033[2K", 20, 1);
        printf("\033[%d;%dH", 20, 1);
        printf("Licznik: %d\n",num);

        printf("\033[%d;%dH", zmienna, 55);
        printf("\n");

        unlock(a);
        i++;
    }
    printf("\033[%d;%dH\033[2K", zmienna, 1);
    return NULL;
}

int main(){
    pthread_t th_tab[WATEK];

    sleep(2);
    printf("\033c");
    int liczba = WATEK*CYKL;
    int i,a;
 
    for(i = 0; i<WATEK; i++){
        a = i;
        if(pthread_create(&(th_tab[i]), NULL, &watki, (void*)&a) != 0){
            perror("PTHREAD CREATE ERROR");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }
    
	int zmienna1 = WATEK+2;
    printf("\n");
    printf("\033[%d;%dH", zmienna1, 1);
    printf("Sekcja prywatna\n");
    printf("\033[%d;%dH", zmienna1, 55);
    printf("Sekcja krytyczna\n");

    for(i = 0; i <WATEK; i++){
        if(pthread_join(th_tab[i], NULL) != 0){
            perror("PTHREAD_JOIN ERROR");
            exit(EXIT_FAILURE);
        }
    }

    
	int zmienna2 = a+WATEK;
    printf("\033[%d;%dH\033[2K", zmienna2, 1);
    printf("\033[%d;%dH\033[2K", zmienna2, 55);
    printf("\033[%d;%dH", zmienna2, 1);
    printf("Wartosc licznika: %d\n", licznik);

    if(licznik == liczba){
        printf("Wartosc licznika zgadza sie z oczekiwana\n");
    }
    else{
        printf("Wartosc licznika nieprawidlowa\n");
    }

  	 printf("\033[12;1H");
	 printf("\033[%d;%dH\033[2K", 20, 1);
    return 0;
}
