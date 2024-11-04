#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

// Definir variables de sincronización
pthread_mutex_t mutex;
sem_t sem; //semaforo para sincronizar el timer con el scheduler
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

// Estructura de PCB
typedef struct {
  int pid;
} PCB;

// Estructura de Cola de Procesos
typedef struct {
  PCB queue[100000];
  int ini;
  int fin;
} process_queue;

process_queue cola_procesos = {0, -1};

// Estructura Machine
typedef struct {
  int CPUs;
  int cores;
  int hilos;
} machine;


void* sche_dispa(void* arg) {
  while(1){
    sem_wait(&sem); //se queda esperando a timer
    printf("Se ha llamado al Scheduler\n");
    pthread_mutex_unlock(&mutex); //desbloquea el mutex para que timer pueda seguir su ejecucución
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
      //Hace lo que tenga que hacer
      sem_post(&sem); //señal para que se ejecute sche_dispa
      pthread_mutex_lock(&mutex); //para evitar que la ejecucion siga antes de que el dispatcher se ejecute
      cont_t = 0;
    }
    else{
      printf("Timer: NO\n");
    }

    done++;
    pthread_cond_signal(&cond1); 
    pthread_cond_wait(&cond2,&mutex);
  }
}


// Funcion Process Generator
void* process_gen(void* arg) {
  pthread_mutex_lock(&mutex);
  while(1){
    cont_p++;
    if (cont_p==mul_p){
      //Hace lo que tenga que hacer

      PCB proc;
      proc.pid = (rand() % 32668) + 100; //Para simular un pid aleatorio
      cola_procesos.fin += 1;
      cola_procesos.queue[cola_procesos.fin] = proc; 

      printf("Pg: %d\n", cola_procesos.queue[cola_procesos.fin].pid);
      cont_p = 0;
    }
    else{
      printf("Pg: NO\n");
    }
    done++;
    pthread_cond_signal(&cond1);
    pthread_cond_wait(&cond2,&mutex);
  }
}



int main(int argc, char* argv[]) {
  
  if (argc != 7) {
    printf("\nUso: %s <frecuencia_clock> <frecuencia_temp> <frecuencia_processGen> <num_cpus> <num_cores> <num_hilos>\n", argv[0]);
    exit(1);
  }

  int freq_c = atoi(argv[1]);
  int freq_t = atoi(argv[2]);
  int freq_p = atoi(argv[3]);
  mul_t = freq_c * freq_t;
  mul_p = freq_c * freq_p;
  cont_t = 0;
  cont_p = 0;

  //Iniciamos las variables de los hilos
  pthread_mutex_init(&mutex, NULL);
  sem_init(&sem, 0, 0);
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
