//Inicializamos las colas
extern cola cola1;
extern cola cola2;
extern cola cola3;// 0 para indicar que es infinito, ya que la ultima cola es FCFS


extern process_queue cola_procesos;

extern machine hardware;
//PCB* maquina[][][];
extern thread**** maquina; // Declaración de puntero para memoria dinámica

extern MemoriaFisica mem_fisica;

//Declarar funciones de funciones.c 
void anadirACola(PCB* proc, int prioridad);
void imprimirColas();
PCB* sacarPCBDeCola();
void asignarEstructura();
void sacarDeEstructura();
void moverEstructura();
void imprimirProcesos();
