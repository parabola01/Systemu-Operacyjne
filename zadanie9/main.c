#define _REENTRANT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define CYKL 3 // liczba sekcji krytycznych
#define WATEK 3 // liczba watkow

pthread_mutex_t myMutex;
int licznik = 0;

void *watki(void *arg){
    srand(time(NULL));
    int rng = 2 + rand() % 3;

    int a = *(int*)arg;

    sleep(1);

    int i=0;
    int zmienna = a+CYKL+WATEK+1;
    while(i<CYKL){
        printf("\033[%d;%dH\033[2K", zmienna, 1);

        printf("Watek nr:%d w sekcji nr:%d\n", a+1, i+1);

        sleep(rng);
        pthread_mutex_lock(&myMutex);

        printf("\033[%d;%dH\033[2K", zmienna, 1);
        printf("\033[%d;%dH",zmienna, 55);
        printf("Watek nr:%d w sekcji nr:%d\n", a+1, i+1);

        int num = licznik;
        num++;
        licznik = num;

        printf("\033[%d;%dH\033[2K",CYKL*WATEK+3, 1);
        printf("\033[%d;%dH", CYKL*WATEK+ 3, 1);
        printf("Licznik: %d\n",num);
        sleep(rng);

        printf("\033[%d;%dH", zmienna, 55);
        printf("\n");

        pthread_mutex_unlock(&myMutex);
        i++;
    }
    printf("\033[%d;%dH\033[2K", zmienna, 1);

    return NULL;
}

int main(){
    pthread_mutex_init(&myMutex, NULL);
    pthread_t th_tab[WATEK];

    printf("\033c");
    printf("Adres muteksu: %p\n", (void*)&myMutex);
    sleep(2);
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
	int zmienna = a+WATEK+1;
	
    printf("\n");
    printf("\033[%d;%dH", zmienna, 1);
    printf("Sekcja prywatna\n");
    printf("\033[%d;%dH", zmienna, 55);
    printf("Sekcja krytyczna\n");

    for(i = 0; i <WATEK; i++){
        if(pthread_join(th_tab[i], NULL) != 0){
            perror("PTHREAD_JOIN ERROR");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&myMutex);

    printf("\033[%d;%dH\033[2K", zmienna, 1);
    printf("\033[%d;%dH\033[2K", zmienna, 55);
    printf("\033[%d;%dH", zmienna, 1);
    printf("Wartosc licznika: %d\n", licznik);

    if(licznik == liczba){
        printf("Wartosc licznika zgadza sie z oczekiwana\n");
    }
    else{
        printf("Wartosc licznika nieprawidlowa\n");
    }

    printf("\033[12;1H");

    return 0;
}

