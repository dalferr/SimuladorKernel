CC = gcc
OBJ = threads.o funciones.o 

sim: sistema.c $(OBJ)
	$(CC) -o sim sistema.c $(OBJ)

funciones.o: funciones.c 
	$(CC) -c funciones.c 

threads.o: threads.c 
	$(CC) -c threads.c 

clean:
	rm -f $(OBJ)
