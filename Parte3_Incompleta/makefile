CC = gcc
OBJ = source/threads.o source/funciones.o 

sim: source/sistema.c $(OBJ)
	$(CC) -o sim source/sistema.c $(OBJ)

funciones.o: source/funciones.c 
	$(CC) -c source/funciones.c 

threads.o: source/threads.c 
	$(CC) -c source/threads.c 

clean:
	rm -f $(OBJ)
