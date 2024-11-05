#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include "threads.h"
//#include "structs.h"


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

  //Inicializamos la estructura machine
  machine maquina = {atoi(argv[4]), atoi(argv[5]), atoi(argv[6])};

  //Iniciamos las variables de los hilos
  pthread_mutex_init(&mutex, NULL);
  sem_init(&sem, 0, 0);
  sem_init(&sem1, 0, 0);
  pthread_cond_init(&cond, NULL);
  pthread_cond_init(&cond1, NULL);
  pthread_cond_init(&cond2, NULL);

  // Creamos los hilos
  pthread_t th_clock;
  pthread_t th_timer;
  pthread_t th_timer1;
  pthread_t th_sche_dispa;
  pthread_t th_process_gen;
  pthread_create(&th_clock, NULL, reloj, NULL);
  pthread_create(&th_timer, NULL, timer, NULL);
  pthread_create(&th_timer1, NULL, timer1, NULL);
  pthread_create(&th_sche_dispa, NULL, sche_dispa, NULL);
  pthread_create(&th_process_gen, NULL, process_gen, NULL);

  // Esperar a que los hilos se junten
  pthread_join(th_clock, NULL);
  pthread_join(th_timer, NULL);
  pthread_join(th_timer1, NULL);
  pthread_join(th_sche_dispa, NULL);
  pthread_join(th_process_gen, NULL);
}
