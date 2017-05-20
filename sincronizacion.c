#include <stdio.h> //standard input/output
#include <pthread.h> //para usar threads
#include <unistd.h>     // para hacer sleep
#include <stdlib.h>     // para libreria de numeros random: srand, rand
#include <time.h>       // para tomar el tiempo
#include <semaphore.h>

sem_t miSemaforo1;
sem_t miSemaforo2;
sem_t miSemaforo3;
sem_t miSemaforo4;
#define NUM_THREADS 4

//cada funcion tocar_movimiento_i toca una parte de la melodia
void* tocar_movimiento_1 (void* parametro){
       sem_wait(&miSemaforo1);
       system("mplayer -really-quiet file_1.mp3");
       sem_post(&miSemaforo2);
       pthread_exit(NULL);
}
void* tocar_movimiento_2 (void* parametro){
       sem_wait(&miSemaforo2);
       system("mplayer -really-quiet file_2.mp3");
       sem_post(&miSemaforo3);
       pthread_exit(NULL);

}

void* tocar_movimiento_3 (void* parametro){
       sem_wait(&miSemaforo3);
       system("mplayer -really-quiet file_3.mp3");
       sem_post(&miSemaforo4);
       pthread_exit(NULL);
}

void* tocar_movimiento_4 (void* parametro){
       sem_wait(&miSemaforo4);
       system("mplayer -really-quiet file_4.mp3");
       pthread_exit(NULL);

}

int main (){
       sem_init(&miSemaforo1,0,1);
       sem_init(&miSemaforo2,0,0);
       sem_init(&miSemaforo3,0,0);
       sem_init(&miSemaforo4,0,0);

       pthread_t threads[NUM_THREADS]; //una variable de tipo pthread_t sirve para identificar cada hilo que se cree
                                   //la variable threads es una array de pthread_t
                                   //comparar con char data[100], un array de char

    //genero los threads y los lanzo, observar que sin semaforos se ejecutan los 4 casi al mismo tiempo
    //y no se reconoce la melodía
    int rc;
       rc = pthread_create(&threads[1], NULL, tocar_movimiento_2, NULL );
       rc = pthread_create(&threads[0], NULL, tocar_movimiento_1, NULL );
       rc = pthread_create(&threads[3], NULL, tocar_movimiento_4, NULL );
       rc = pthread_create(&threads[2], NULL, tocar_movimiento_3, NULL );

    //esperar a que los threads terminen para terminar el programa principal
    int i;
        for(i = 0 ; i < NUM_THREADS ; i++)
        {
            pthread_join(threads[i] , NULL);
        }
    sem_destroy(&miSemaforo1);
    sem_destroy(&miSemaforo2);
    sem_destroy(&miSemaforo3);
    sem_destroy(&miSemaforo4);
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}

//Para compilar:   gcc 5ta_sinfonia_intro.c -o 5ta_sinfonia_intro -lpthread
//Para ejecutar:   ./5ta_sinfonia_intro
