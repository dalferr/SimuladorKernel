#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>


// Estructura de PCB
typedef struct {
  int pid;
  int vida;
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
