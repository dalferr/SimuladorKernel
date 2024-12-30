// Definir variables de sincronización
pthread_mutex_t mutex;
sem_t sem; //semaforo para sincronizar el timer con el scheduler
sem_t sem1; //semaforo para sincronizar el timer con el scheduler
sem_t sem2; //semaforo para sincronizar el timer con el scheduler
sem_t sem3; //semaforo para sincronizar el timer con el scheduler
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
int prioridad;


//Inicializamos las colas
cola cola1;
cola cola2;
cola cola3;// 0 para indicar que es infinito, ya que la ultima cola es FCFS


process_queue cola_procesos;

machine hardware;
//PCB* maquina[][][];
PCB**** maquina; // Declaración de puntero para memoria dinámica
