# Simulador de Kernel

## Introducción

En la parte teórica de la asignatura de Sistemas Operativos se estudian los principales elementos de un kernel: gestión y planificación de procesos, sistema de memoria y entrada/salida. Además, en el último tema se expondrán las medidas de seguridad que se implementan en los kernels y los tipos de ataques que han surgido en los últimos años. Asimismo, con esta práctica se trabajará el lenguaje de programación C, que también se utiliza en otras asignaturas de la especialidad de Ingeniería de Computadores.

## Objetivo

El objetivo de esta práctica es desarrollar un simulador de un kernel. El trabajo se divide en tres partes.

### 1ª parte: Arquitectura del Sistema

En esta primera parte se definirá la arquitectura del sistema. Aquí es fundamental preparar el sistema para realizar las siguientes partes de la práctica. Para ello, es necesario definir las estructuras de datos necesarias para las simulaciones e implementar el hilo principal que gestionará todo el sistema. Este hilo tendrá varias tareas, por ejemplo, la gestión del reloj del sistema.

### 2ª parte: Planificador

El planificador (o scheduler) gestiona la ejecución de los procesos. En la construcción de este subsistema se pueden utilizar diversas políticas y arquitecturas. En esta parte, teniendo en cuenta la descripción del hardware proporcionado, se deberá implementar una (o varias) política que maximice la eficiencia y el rendimiento de los procesos.

### 3ª parte: Gestor de Memoria

Un kernel utiliza direcciones virtuales y físicas para gestionar la memoria. Los procesos emplean direcciones virtuales, y el procesador realiza la traducción para obtener las direcciones físicas correspondientes mediante el TLB y la MMU. En esta parte se deberá implementar este proceso. Cada proceso que se ejecute tendrá un listado de accesos a la memoria, y el sistema simulado deberá llevar a cabo un proceso de traducción para realizar lecturas o escrituras en la memoria física.
