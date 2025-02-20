# SimuladorKernel

Este proyecto es un simulador de un kernel desarrollado para la asignatura de Sistemas Operativos de la carrera Ingeniería Informática . Su objetivo es plasmar en código los conceptos teóricos estudiados, como la gestión y planificación de procesos, la simulación del sistema de memoria y aspectos de seguridad, utilizando ANSI C. 

- Una versión **mas extensa** de la **documentación** está en -> [Documentación]https://github.com/dalferr/SimuladorKernel/blob/master/Documentacion.pdf
## Código

- **sistema.c:** Contiene las inicializaciones de las variables y estructuras que se utilizarán. Además incluye la función main(), que se encargará de inicializar los hilos.
- **threads.c:** Contiene los hilos que se encargarán de simular el reloj, el Process Generator y el Scheduler/Dispatcher.
- **funciones.c**: Contiene las funciones auxiliares a las que llamarán los hilos.

## Uso
### Compilación
```bash
make
make clean
```
### Ejecución 
Si ejecutamos el programa veremos que nos pedirá los siguientes parámetros:
```bash
Uso: ./sim <frecuencia_clock> <frecuencia_temp> <frecuencia_processGen> <num_cpus> <num_cores> <num_hilos>
```
#### Parámetros
- **<frecuencia_clock>**: Entero > 0. Esto indicará la frecuencia del reloj, es decir, la frecuencia de los ciclos que controlan el tiempo del sistema.
- **<frecuencia_temp>**: Entero > 0. Esto indicará la frecuencia del temporizador que llamará al scheduler, es decir, cada cuantos ciclos de reloj se ejecutará el scheduler.
- **<frecuencia_processGen>**: Entero > 0. Indicará la frecuencia con la que se le llame al proccess generator, es decir, la frecuencia con la que se generará un nuevo proceso.
- **<num_cpus>**: Entero > 0. Indicará el número de procesadores que tendrá la máquina que simularemos.
- **<num_cores>**: Entero > 0. Indicará el número de núcleos que tendrá cada procesador.
- **<num_hilos>**: Entero > 0. Indicará el número hilos que tendrá cada core.
### Salida
Al ejecutarlo con los parámetros correspondientes, veremos que por cada pulso de reloj imprime por pantalla el estado del Scheduler/Dispatcher y del Process Generator, los procesos en ejecución junto al estado de cada proceso, y las colas con su contenido. 
El programa imprime el código muy rápido, por lo que para analizarlo una solución es redirigir la salida a un fichero:
```bash
./sim 1 2 1 1 2 3 > ej.txt
```
La ejecución del programa es infinita, por lo que cuando queramos que pare debemos pulsar Ctrl+C.
#### Ejemplo
Ejecutamos el programa con los siguientes parámetros:
```bash
./sim 1 2 1 1 2 3 > ej.txt
```
La salida será la siguiente:
```c
Scheduler: NO  //Indica que el scheduler no se ejecuta  
Pg: 3175 Cola: 1  //Se crea el proceso 3175 y se le asigna la cola 1  
----------------------------------------------------------  
***PROCESOS EN EJECUCIÓN***        //Como no se ha ejecutado  
CPU: 0, Core: 0, Thread: 0 --->    //el scheduler/dispatcher  
CPU: 0, Core: 0, Thread: 1 --->    //el proceso no entra en ejecucción  
CPU: 0, Core: 0, Thread: 2 --->  
CPU: 0, Core: 1, Thread: 0 --->  
CPU: 0, Core: 1, Thread: 1 --->  
CPU: 0, Core: 1, Thread: 2 --->  
----------------------------------------------------------  
***COLAS***  
#####Cola 1#####  
PID: 3175, VIDA: 7, Q: 5   //Se indica que el proceso está en la cola 1  
#####Cola 2#####           // y su vida y quantum  
#####Cola 3#####  
----------------------------------------------------------  
Se ha llamado al Scheduler   //Se ejecuta el Scheduler/Dispatcher  
Pg: 24367 Cola: 2            //Se crea proceso nuevo  
----------------------------------------------------------  
***PROCESOS EN EJECUCIÓN***  
CPU: 0, Core: 0, Thread: 0 ---> PID: 3175, VIDA: 7, Q: 5, Cola: 1  
CPU: 0, Core: 0, Thread: 1 --->   //El proceso entra en ejecución  
CPU: 0, Core: 0, Thread: 2 --->  
CPU: 0, Core: 1, Thread: 0 --->  
CPU: 0, Core: 1, Thread: 1 --->  
CPU: 0, Core: 1, Thread: 2 --->  
----------------------------------------------------------  
***COLAS***  
#####Cola 1#####  
#####Cola 2#####  
PID: 24367, VIDA: 14, Q: 10  //El proceso nuevo se queda en la cola  
#####Cola 3#####  
----------------------------------------------------------  
Pg: 13438 Cola: 1  
Scheduler: NO   //No se ejecuta el scheduler/dispatcher  
----------------------------------------------------------  
***PROCESOS EN EJECUCIÓN***  
CPU: 0, Core: 0, Thread: 0 ---> PID: 3175, VIDA: 6, Q: 4, Cola: 1  
CPU: 0, Core: 0, Thread: 1 --->   //Disminuye la vida y quantum de  
CPU: 0, Core: 0, Thread: 2 --->   //los procesos en ejecución  
CPU: 0, Core: 1, Thread: 0 --->  
CPU: 0, Core: 1, Thread: 1 --->  
CPU: 0, Core: 1, Thread: 2 --->  
----------------------------------------------------------  
***COLAS***  
#####Cola 1#####  
PID: 13438, VIDA: 13, Q: 5  
#####Cola 2#####  
PID: 24367, VIDA: 14, Q: 10  
#####Cola 3#####  
----------------------------------------------------------  
Pg: 3633 Cola: 2  
Se ha llamado al Scheduler  //Mete a ejecución los procesos en las colas  
----------------------------------------------------------  
***PROCESOS EN EJECUCIÓN***  
CPU: 0, Core: 0, Thread: 0 ---> PID: 3175, VIDA: 5, Q: 3, Cola: 1  
CPU: 0, Core: 0, Thread: 1 ---> PID: 13438, VIDA: 13, Q: 5, Cola: 1  
CPU: 0, Core: 0, Thread: 2 ---> PID: 24367, VIDA: 14, Q: 10, Cola: 2  
CPU: 0, Core: 1, Thread: 0 ---> PID: 3633, VIDA: 3, Q: 10, Cola: 2  
CPU: 0, Core: 1, Thread: 1 --->  
CPU: 0, Core: 1, Thread: 2 --->  
----------------------------------------------------------  
***COLAS***  
#####Cola 1#####  
#####Cola 2#####  
#####Cola 3#####**
```
