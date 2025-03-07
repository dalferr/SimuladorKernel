#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>


// Estructura de PCB
typedef struct PCB {
  int pid;
  int vida;
  int quantum;
  int cola;
  struct PCB* sig;
} PCB;


// Estructura de Cola de Procesos
typedef struct {
  PCB* prim;
  PCB* ult;
  int cant;
  int quantum;
} cola;



// Estructura de Cola de Procesos
typedef struct {
  cola cola1;
  cola cola2;
  cola cola3;
} process_queue;
  


// Estructura Machine
typedef struct {
  int cpus;
  int cores;
  int hilos;
} machine;


