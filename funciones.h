
void anadirACola(PCB* proc, int prioridad) {
  if (prioridad == 1) {
    if (cola_procesos.cola1.cant == 0){
      proc->sig = NULL;
      cola_procesos.cola1.prim = proc;
      cola_procesos.cola1.ult = proc;
      cola_procesos.cola1.cant = 1;
    } 
    else {
      cola_procesos.cola1.ult->sig = proc;
      cola_procesos.cola1.ult = proc;
      proc->sig = NULL;
      cola_procesos.cola1.cant += 1;
    }
    printf("Pg: %d Cola: 1\n", cola_procesos.cola1.ult->pid);
    fflush(stdout);
  }
  else if (prioridad == 2) {
    if (cola_procesos.cola2.cant == 0){
      proc->sig = NULL;
      cola_procesos.cola2.prim = proc;
      cola_procesos.cola2.ult = proc;
      cola_procesos.cola2.cant = 1;
    } 
    else {
      cola_procesos.cola2.ult->sig = proc;
      cola_procesos.cola2.ult = proc;
      proc->sig = NULL;
      cola_procesos.cola2.cant += 1;
    }
    printf("Pg: %d Cola: 2\n", cola_procesos.cola2.ult->pid);
    fflush(stdout);
  }
  else if (prioridad == 3) {
    if (cola_procesos.cola3.cant == 0){
      proc->sig = NULL;
      cola_procesos.cola3.prim = proc;
      cola_procesos.cola3.ult = proc;
      cola_procesos.cola3.cant = 1;
    } 
    else {
      cola_procesos.cola3.ult->sig = proc;
      cola_procesos.cola3.ult = proc;
      proc->sig = NULL;
      cola_procesos.cola3.cant += 1;
    }
    printf("Pg: %d Cola: 3\n", cola_procesos.cola3.ult->pid);
    fflush(stdout);
  }
}

void imprimirColas(){
  printf("----------------------------------------------------------\n");
  PCB* proc;

  printf("#####Cola 1#####\n");
  if (cola_procesos.cola1.cant != 0){
    proc = cola_procesos.cola1.prim;
    printf("PID: %d\n", proc->pid);
    while (proc->sig != NULL){
      proc = proc->sig;
      printf("PID: %d\n", proc->pid);
    }
  }

  printf("#####Cola 2#####\n");
  if (cola_procesos.cola2.cant != 0){
    proc = cola_procesos.cola2.prim;
    printf("PID: %d\n", proc->pid);
    while (proc->sig != NULL){
      proc = proc->sig;
      printf("PID: %d\n", proc->pid);
    }
  }

  printf("#####Cola 3#####\n");
  if (cola_procesos.cola3.cant != 0){
    proc = cola_procesos.cola3.prim;
    printf("PID: %d\n", proc->pid);
    while (proc->sig != NULL){
      proc = proc->sig;
      printf("PID: %d\n", proc->pid);
    }
  }

  printf("----------------------------------------------------------\n");
  fflush(stdout);
}

void asignarEstructura(){
  for (int cpu = 0; cpu < hardware.cpus; cpu++){
    for (int core = 0; core < hardware.cores; core++){
      for (int hilo = 0; hilo < hardware.hilos; hilo++){

      }
    }
  }
}

void moverEstructura(){
  for (int cpu = 0; cpu < hardware.cpus; cpu++){
    for (int core = 0; core < hardware.cores; core++){
      for (int hilo = 0; hilo < hardware.hilos; hilo++){
        PCB* mi_hilo = maquina[cpu][core][hilo];
        if (mi_hilo != NULL){
          if (mi_hilo->vida != 0 ){
            mi_hilo->vida--; //Los borra el dispatcher
          }
        }
      }
    }
  }
}
