#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include "structs.h"
#include "threads.h"
//#include "funciones.h"



void* sche_dispa(void* arg) {
  while(1){
    sem_wait(&sem); //se queda esperando a timer
    printf("Se ha llamado al Scheduler\n");
    fflush(stdout);

    sacarDeEstructura(); //Elimina los procesos acabados de la estrcutura y los a los que se les ha acabado el quantum los manda a la siguiente cola.
    asignarEstructura(); //Mueve los PCBs de las colas a la estructura.

    sem_post(&sem1);
  }
}

void* process_gen(void* arg) {
  while(1){
    sem_wait(&sem2); //se queda esperando a timer
      //PCB proc;
      PCB* proc = (PCB*)malloc(sizeof(PCB));
      proc->pid = (rand() % 32668) + 100; //Para simular un pid aleatorio
      proc->vida = (rand() % 20) + 1; //Para simular un tiempo de vida aleatorio
      prioridad = (rand() % 3) + 1; //Para simular un nivel de prioridad aleatorio del 1 al 3
    //
     anadirACola(proc, prioridad);

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

    //printf("-----------------------------------------------------------\n");
    //fflush(stdout);

    imprimirProcesos();
    imprimirColas();    
    moverEstructura();

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
    printf("Scheduler: NO\n");
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

