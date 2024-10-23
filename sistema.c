#include <stdio.h>
#include <pthread.h>

// Definir variables de sincronización
pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_cond_t cond1;
pthread_cond_t cond2;

// Definir variables globales
int done = 0;
int tenp_kont = 2;

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


void* sche_dispa(void* arg) {
  printf("Se ha llamado al Scheduler\n");
  return NULL;
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
 // int freq = *((int*)arg); // Cast para convertir void* en puntero
  pthread_mutex_lock(&mutex);
  while(1){
    done++;
    
    //sche_dispa(NULL);
    printf("Ciclo en el timer\n");

    pthread_cond_signal(&cond1); 
    pthread_cond_wait(&cond2,&mutex);
    //pthread_mutex_unlock(&mutex);
  }
}


// Funcion Process Generator
void* process_gen(void* arg) {
  //int freq = *((int*)arg); // Cast para convertir void* en puntero
  pthread_mutex_lock(&mutex);
  while(1){
    done++;


    printf("Ciclo en el Process Generator\n");

    pthread_cond_signal(&cond1);
    pthread_cond_wait(&cond2,&mutex);
    //pthread_mutex_unlock(&mutex);
  }
}



int main(int argc, char* argv[]) {

  //Iniciamos las variables de los hilos
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
  pthread_cond_init(&cond1, NULL);
  pthread_cond_init(&cond2, NULL);

  // Creamos los hilos
  pthread_t th_clock;
  pthread_t th_timer;
  pthread_t th_process_gen;
  pthread_t th_sche_dispa;
  pthread_create(&th_clock, NULL, reloj, NULL);
  pthread_create(&th_timer, NULL, timer, NULL);
  pthread_create(&th_process_gen, NULL, process_gen, NULL);
  pthread_create(&th_sche_dispa, NULL, sche_dispa, NULL);

  // Esperar a que los hilos se junten
  pthread_join(th_clock, NULL);
  pthread_join(th_timer, NULL);
  pthread_join(th_process_gen, NULL);
  pthread_join(th_sche_dispa, NULL);
}
