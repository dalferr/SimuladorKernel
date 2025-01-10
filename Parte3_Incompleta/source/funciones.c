#include <string.h>
#include "../include/structs.h"
#include "../include/funciones.h"

void anadirACola(PCB* proc, int prioridad) {
  if (prioridad == 1) {
    if (cola_procesos.cola1.cant == 0){
      proc->sig = NULL;
      proc->cola = 1;
      proc->quantum = cola_procesos.cola1.quantum;
      cola_procesos.cola1.prim = proc;
      cola_procesos.cola1.ult = proc;
      cola_procesos.cola1.cant = 1;
    } 
    else {
      cola_procesos.cola1.ult->sig = proc;
      cola_procesos.cola1.ult = proc;
      proc->sig = NULL;
      proc->cola = 1;
      proc->quantum = cola_procesos.cola1.quantum;
      cola_procesos.cola1.cant += 1;
    }
    printf("Pg: %d Cola: 1\n", cola_procesos.cola1.ult->pid);
    fflush(stdout);
  }
  else if (prioridad == 2) {
    if (cola_procesos.cola2.cant == 0){
      proc->sig = NULL;
      proc->cola = 2;
      proc->quantum = cola_procesos.cola2.quantum;
      cola_procesos.cola2.prim = proc;
      cola_procesos.cola2.ult = proc;
      cola_procesos.cola2.cant = 1;
    } 
    else {
      cola_procesos.cola2.ult->sig = proc;
      cola_procesos.cola2.ult = proc;
      proc->sig = NULL;
      proc->cola = 2;
      proc->quantum = cola_procesos.cola2.quantum;
      cola_procesos.cola2.cant += 1;
    }
    printf("Pg: %d Cola: 2\n", cola_procesos.cola2.ult->pid);
    fflush(stdout);
  }
  else if (prioridad == 3) {
    if (cola_procesos.cola3.cant == 0){
      proc->sig = NULL;
      proc->cola = 3;
      proc->quantum = cola_procesos.cola3.quantum;
      cola_procesos.cola3.prim = proc;
      cola_procesos.cola3.ult = proc;
      cola_procesos.cola3.cant = 1;
    } 
    else {
      cola_procesos.cola3.ult->sig = proc;
      cola_procesos.cola3.ult = proc;
      proc->sig = NULL;
      proc->cola = 3;
      proc->quantum = cola_procesos.cola3.quantum;
      cola_procesos.cola3.cant += 1;
    }
    printf("Pg: %d Cola: 3\n", cola_procesos.cola3.ult->pid);
    fflush(stdout);
  }
}

void imprimirColas(){
  printf("\n----------------------------------------------------------\n");
  printf("***COLAS***");
  PCB* proc;

  printf("\n#####Cola 1#####\n");
  if (cola_procesos.cola1.cant != 0){
    proc = cola_procesos.cola1.prim;
    printf("PID: %d, VIDA: %d, Q: %d\n", proc->pid, proc->vida, proc->quantum);
    while (proc->sig != NULL){
      proc = proc->sig;
      printf("PID: %d, VIDA: %d, Q: %d\n", proc->pid, proc->vida, proc->quantum);
    }
  }

  printf("#####Cola 2#####\n");
  if (cola_procesos.cola2.cant != 0){
    proc = cola_procesos.cola2.prim;
    printf("PID: %d, VIDA: %d, Q: %d\n", proc->pid, proc->vida, proc->quantum);
    while (proc->sig != NULL){
      proc = proc->sig;
      printf("PID: %d, VIDA: %d, Q: %d\n", proc->pid, proc->vida, proc->quantum);
    }
  }

  printf("#####Cola 3#####\n");
  if (cola_procesos.cola3.cant != 0){
    proc = cola_procesos.cola3.prim;
    printf("PID: %d, VIDA: %d, Q: %d\n", proc->pid, proc->vida, proc->quantum);
    while (proc->sig != NULL){
      proc = proc->sig;
      printf("PID: %d, VIDA: %d, Q: %d\n", proc->pid, proc->vida, proc->quantum);
    }
  }

  printf("----------------------------------------------------------\n");
  fflush(stdout);
}

PCB* sacarPCBDeCola(){
  PCB* proceso;
  if (cola_procesos.cola1.cant > 0){
    proceso = cola_procesos.cola1.prim;
    cola_procesos.cola1.prim = proceso->sig;
    cola_procesos.cola1.cant--;
    proceso->sig = NULL;
  }
  else if (cola_procesos.cola2.cant > 0){
    proceso = cola_procesos.cola2.prim;
    cola_procesos.cola2.prim = proceso->sig;
    cola_procesos.cola2.cant--;
    proceso->sig = NULL;
  }
  else if (cola_procesos.cola3.cant > 0){
    proceso = cola_procesos.cola3.prim;
    cola_procesos.cola3.prim = proceso->sig;
    cola_procesos.cola3.cant--;
    proceso->sig = NULL;
  }
  else {
    proceso = NULL;
  }
  return proceso;
}


void asignarEstructura(){
  for (int cpu = 0; cpu < hardware.cpus; cpu++){
    for (int core = 0; core < hardware.cores; core++){
      for (int hilo = 0; hilo < hardware.hilos; hilo++){
        PCB* proceso = maquina[cpu][core][hilo]->pcb;
        if (proceso == NULL){
          maquina[cpu][core][hilo]->pcb = sacarPCBDeCola();
        }
      }
    }
  }
}

void sacarDeEstructura(){
  for (int cpu = 0; cpu < hardware.cpus; cpu++){
    for (int core = 0; core < hardware.cores; core++){
      for (int hilo = 0; hilo < hardware.hilos; hilo++){
        PCB* proceso = maquina[cpu][core][hilo]->pcb;
        if (proceso != NULL){
          if (proceso->vida <= 0){
            free(proceso);
            maquina[cpu][core][hilo]->pcb = NULL;
          }
          else if ((proceso->quantum <= 0) && (proceso->cola == 1)){ //Si se le acaba el quantum vuelta a la cola
            maquina[cpu][core][hilo]->pcb = NULL;
            anadirACola(proceso, 2);
          }
          else if ((proceso->quantum <= 0) && (proceso->cola == 2)){ //Si se le acaba el quantum vuelta a la cola
            maquina[cpu][core][hilo]->pcb = NULL;
            anadirACola(proceso, 3);
          }
        }
      }
    }
  }
}

void moverEstructura(){
  for (int cpu = 0; cpu < hardware.cpus; cpu++){
    for (int core = 0; core < hardware.cores; core++){
      for (int hilo = 0; hilo < hardware.hilos; hilo++){
        PCB* proceso = maquina[cpu][core][hilo]->pcb;
        if (proceso != NULL){
          if (proceso->vida != 0 ){
            if (proceso->cola == 3) {
              proceso->quantum = -1;
            }
            else {
              proceso->quantum--;
            }
            proceso->vida--; //Los borra el dispatcher
            maquina[cpu][core][hilo]->pcb = proceso;
          }
        }
      }
    }
  }
}

void imprimirProcesos(){
  printf("----------------------------------------------------------\n");
  printf("***PROCESOS EN EJECUCIÓN***");
  for (int cpu = 0; cpu < hardware.cpus; cpu++){
    for (int core = 0; core < hardware.cores; core++){
      for (int hilo = 0; hilo < hardware.hilos; hilo++){
        printf("\nCPU: %d, Core: %d, Thread: %d --->", cpu, core, hilo);
        PCB* proceso = maquina[cpu][core][hilo]->pcb;
        if (proceso != NULL){
          printf(" PID: %d, VIDA: %d, Q: %d, Cola: %d", proceso->pid, proceso->vida, proceso->quantum, proceso->cola);
        }
      }
    }
  }
  fflush(stdout);
}

int buscarPosLibre(){
  int pos = 0;
  while (mem_fisica.restoMemoria != NULL){
    pos++;
  }
  return pos;
}

void cargarFichero(const char *nombreArchivo, PCB* proc) {
    FILE *archivo = fopen(nombreArchivo, "r");  // Abre el archivo en modo lectura
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char *linea = NULL;       // Puntero para almacenar la línea
    size_t longitud = 0;      // Variable para el tamaño del buffer de getline
    ssize_t leidos;           // Almacena el número de caracteres leídos

    int cont = 1;

    int pos = buscarPosLibre();

    while ((leidos = getline(&linea, &longitud, archivo)) != -1) {
      if (cont == 1){
        cont++;
        char *valor = strchr(linea, ' ');
        valor++;
        
        mem_fisica.restoMemoria[pos] = valor;
        proc->mm.code = mem_fisica.restoMemoria[pos];
        pos++;

      //printf("%s",valor);
    }
    else if (cont == 2) {
      cont++;
      char *valor = strchr(linea, ' ');
      valor++;

      mem_fisica.restoMemoria[pos] = valor;
      proc->mm.data = mem_fisica.restoMemoria[pos];
      pos++;

      //printf("%s",valor);
    }
    else {

      //printf("%s", linea);  // Imprime la línea leída
    }
    }

    free(linea);              // Libera la memoria asignada por getline
    fclose(archivo);          // Cierra el archivo
}
