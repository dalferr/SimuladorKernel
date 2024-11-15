#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>


// Estructura de PCB
typedef struct {
  int pid;
  int vida;
  struct PCB* sig;
} PCB;

/*
// Estructura de Cola de Procesos
typedef struct {
  PCB queue[100000];
  int ini;
  int fin;
} process_queue;

process_queue cola_procesos = {0, -1};
*/ 

// Estructura de Cola de Procesos
typedef struct {
  //struct PCB* prim;
  //struct PCB* ult;
  PCB* prim;
  PCB* ult;
  int cant;
  int quantum;
} cola;

  //Inicializamos las colas
  cola cola1;
  cola cola2;
  cola cola3;// 0 para indicar que es infinito, ya que la ultima cola es FCFS



// Estructura de Cola de Procesos
typedef struct {
  cola cola1;
  cola cola2;
  cola cola3;
} process_queue;
  
process_queue cola_procesos;

// Estructura Machine
typedef struct {
  int cpus;
  int cores;
  int hilos;
} machine;

machine hardware;
//PCB* maquina[][][];
PCB**** maquina; // Declaración de puntero para memoria dinámica
