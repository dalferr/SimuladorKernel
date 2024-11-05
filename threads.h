#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include "structs.h"


// Definir variables de sincronización
pthread_mutex_t mutex;
sem_t sem; //semaforo para sincronizar el timer con el scheduler
sem_t sem1; //semaforo para sincronizar el timer con el scheduler
pthread_cond_t cond;
pthread_cond_t cond1;
pthread_cond_t cond2;

// Definir variables globales
int done = 0;
int tenp_kont = 2;
int freq_c;
int mul_t;
int mul_p;
int cont_t;
int cont_p;




void* sche_dispa(void* arg) {
  while(1){
    sem_wait(&sem); //se queda esperando a timer
    printf("Se ha llamado al Scheduler\n");
    fflush(stdout);
  }
}

void* process_gen(void* arg) {
  while(1){
    sem_wait(&sem1); //se queda esperando a timer
    PCB proc;
      proc.pid = (rand() % 32668) + 100; //Para simular un pid aleatorio
      proc.vida = (rand() % 20) + 1; //Para simular un tiempo de vida aleatorio
      cola_procesos.fin += 1;
      cola_procesos.queue[cola_procesos.fin] = proc; 

    printf("Pg: %d\n", cola_procesos.queue[cola_procesos.fin].pid);
    fflush(stdout);
  }
}

// FUncion clock
void* reloj(void* arg) {
  while(1){
    pthread_mutex_lock(&mutex);
    while(done<tenp_kont){
      pthread_cond_wait(&cond1, &mutex);
    }
    done=0;
    pthread_cond_broadcast(&cond2);
    pthread_mutex_unlock(&mutex);
  }
}


/// Funcion timer
void* timer(void* arg) {
  pthread_mutex_lock(&mutex);
  while(1){
    cont_t++;
    if (cont_t==mul_t){
      sem_post(&sem); //señal para que se ejecute sche_dispa
      cont_t = 0;
    }
    else{
      printf("Timer: NO\n");
    fflush(stdout);
    }

    done++;
    pthread_cond_signal(&cond1); 
    pthread_cond_wait(&cond2,&mutex);
  }
}


// Funcion Process Generator
void* timer1(void* arg) {
  pthread_mutex_lock(&mutex);
  while(1){
    cont_p++;
    if (cont_p==mul_p){
      sem_post(&sem1); //señal para que se ejecute process_gen
      cont_p = 0;
    }
    else{
      printf("Pg: NO\n");
      fflush(stdout);
    }
    done++;
    pthread_cond_signal(&cond1);
    pthread_cond_wait(&cond2,&mutex);
  }
}

