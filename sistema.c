#include <stdio.h>
#include <pthread.h>

// Definir variables de sincronización
pthread_mutex_t mutex;
pthread_cond_t cond1;
pthread_cond_t cond2;

// Definir variables globales
int done = 0;
int tenp_kont=2;

// Estructura de PCB
typedef struct {
  int pid;
} PCB;

// Estructura de Cola de Procesos
typedef struct {
  PCB queue[1000];
  int principio;
  int fin;
} process_queue;

// Estructura Machine
typedef struct {
  int CPUs;
  int cores;
  int hilos;
} machine;


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
void* timer(int freq) {
  pthread_mutex_lock(&mutex);
  while(1){
    done++;
    
    //Añadir auqui lo que hace
    for (int i=0;i<freq;i++) {

    }

    pthread_cond_signal(&cond1);
    pthread_cond_wait(&cond2,&mutex);
  }
}


// Funcion Process Generator
void* process_gen(int freq) {
  pthread_mutex_lock(&mutex);
  while(1){
    done++;

    for (int i=0;i<freq;i++) {

    }

    pthread_cond_signal(&cond1);
    pthread_cond_wait(&cond2,&mutex);
  }
}

// FUncion clock
void* sche_dispa(void* arg) {
  printf("Se ha llamado al Scheduler\n");
}

int main(int freq_temp, int freq_sche, int freq_PCB, int hilos, int cores, int CPUs) {

  // Creamos los hilos
  pthread_t th_clock;
  pthread_t th_timer;
  pthread_t th_process_gen;
  pthread_t th_sche_dispa;
  pthread_create(&th_clock, NULL, clock, NULL);
  pthread_create(&th_timer, NULL, timer, NULL);
  pthread_create(&th_process_gen, NULL, process_gen, NULL);
  pthread_create(&th_sche_dispa, NULL, sche_dispa, NULL);
}
