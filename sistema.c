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
  int cpus = atoi(argv[4]);
  int cores = atoi(argv[5]);
  int hilos = atoi(argv[6]);
  mul_t = freq_c * freq_t;
  mul_p = freq_c * freq_p;
  cont_t = 0;
  cont_p = 0;


  hardware.cpus = atoi(argv[4]);
  hardware.cores = atoi(argv[5]);
  hardware.hilos = atoi(argv[6]);

  //Inicializamos la estructura machine
  //maquina[hardware.cpus][hardware.cores][hardware.hilos];
  // Inicializamos la estructura machine (arreglo tridimensional dinámico)
    maquina = (PCB****)malloc(hardware.cpus * sizeof(PCB***));
    for (int i = 0; i < hardware.cpus; i++) {
        maquina[i] = (PCB***)malloc(hardware.cores * sizeof(PCB**));
        for (int j = 0; j < hardware.cores; j++) {
            maquina[i][j] = (PCB**)malloc(hardware.hilos * sizeof(PCB*));
            for (int k = 0; k < hardware.hilos; k++) {
                maquina[i][j][k] = NULL; // Inicializamos cada puntero a NULL
            }
        }
    }

  //Asignamos los valores a las colas
  cola1.quantum=5;
  cola1.cant=0;
  cola2.quantum=10;
  cola2.cant=0;
  cola3.quantum=0; // 0 para indicar que es infinito, ya que la ultima cola es FCFS
  cola3.cant=0;
  cola_procesos.cola1 = cola1;
  cola_procesos.cola2 = cola2;
  cola_procesos.cola3 = cola3;


  //Iniciamos las variables de los hilos
  pthread_mutex_init(&mutex, NULL);
  sem_init(&sem, 0, 0);
  sem_init(&sem1, 0, 0);
  sem_init(&sem2, 0, 0);
  sem_init(&sem3, 0, 0);
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
