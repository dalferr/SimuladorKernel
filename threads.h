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
sem_t sem2; //semaforo para sincronizar el timer con el scheduler
sem_t sem3; //semaforo para sincronizar el timer con el scheduler
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
    sem_post(&sem1);
  }
}

void* process_gen(void* arg) {
  while(1){
    sem_wait(&sem2); //se queda esperando a timer
    PCB proc;
      proc.pid = (rand() % 32668) + 100; //Para simular un pid aleatorio
      proc.vida = (rand() % 20) + 1; //Para simular un tiempo de vida aleatorio
      int prioridad = (rand() % 3) + 1; //Para simular un nivel de prioridad aleatorio del 1 al 3

      if (prioridad == 1) {
        cola_procesos.cola1.fin += 1;
        cola_procesos.cola1.queue[cola_procesos.cola1.fin] = proc;
        printf("Pg: %d Cola: 1\n", cola_procesos.cola1.queue[cola_procesos.cola1.fin].pid);
        fflush(stdout);
      }
      else if (prioridad == 2) {
        cola_procesos.cola2.fin += 1;
        cola_procesos.cola2.queue[cola_procesos.cola2.fin] = proc;
        printf("Pg: %d Cola: 2\n", cola_procesos.cola2.queue[cola_procesos.cola2.fin].pid);
        fflush(stdout);
      }
      else if (prioridad == 3) {
        cola_procesos.cola3.fin += 1;
        cola_procesos.cola3.queue[cola_procesos.cola1.fin] = proc;
        printf("Pg: %d Cola: 3\n", cola_procesos.cola3.queue[cola_procesos.cola3.fin].pid);
        fflush(stdout);
      }

    sem_post(&sem3);
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
      sem_wait(&sem1);
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
      sem_post(&sem2); //señal para que se ejecute process_gen
      sem_wait(&sem3);
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

