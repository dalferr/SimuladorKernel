#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>


typedef struct {
  char *dir_virtual;
  char* *dir_fisica;
} EntradaTablaPaginas;

typedef struct {
    EntradaTablaPaginas entrada[50]; //Para cada pagina asignamos 50 entradas 
} TablaPaginas;

typedef struct {
  //Si el bus de memoria tiene 24 bits, la memoria tiene 2^24 posiciones. 
  //Si las palabras son de 4 Bytes (4*8 bits), nos quedamos con (2^24)/(4*8)= 524288 posiciones
  //De las 524288, dejaremos 2500 para el kernel(Tabla de paginas)
  TablaPaginas kernel[50]; //Supondremos que podemos cargar maximo 50 procesos simultaneos
  char *restoMemoria[521788];
} MemoriaFisica;

//Estructura mm para el PCB
typedef struct {
  char* *code;
  char* *data;
  TablaPaginas* pgb;
} MM;

// Estructura de PCB
typedef struct PCB {
  int pid;
  int vida;
  int quantum;
  int cola;
  MM mm;
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

typedef struct {
  uint32_t* ptbr;
  int pc;
  PCB* pcb;
} thread;
