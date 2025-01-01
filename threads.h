// Definir variables de sincronización
extern pthread_mutex_t mutex;
extern sem_t sem; //semaforo para sincronizar el timer con el scheduler
extern sem_t sem1; //semaforo para sincronizar el timer con el scheduler
extern sem_t sem2; //semaforo para sincronizar el timer con el scheduler
extern sem_t sem3; //semaforo para sincronizar el timer con el scheduler
extern pthread_cond_t cond;
extern pthread_cond_t cond1;
extern pthread_cond_t cond2;

// Definir variables globales
extern int done;
extern int tenp_kont;
extern int freq_c;
extern int mul_t;
extern int mul_p;
extern int cont_t;
extern int cont_p;
extern int prioridad;

//Declarar las funciones externas 
extern void sacarDeEstructura();
extern void asignarEstructura();
extern void anadirACola(PCB* proc, int prioridad);
extern void imprimirProcesos();
extern void imprimirColas();
extern void moverEstructura();
