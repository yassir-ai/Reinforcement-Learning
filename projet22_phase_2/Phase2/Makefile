# compilateur
CC = gcc
# options 
CFLAGS =  -lSDL2 -lSDL2_image  -g -Wall -Wextra 
# liste des fichiers objets
OBJ = main.o code.o
# regle de production finale tp :
prog : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o prog  
	rm -rf  *.o
	@echo "Lancer le programme avec  ./prog"
# regle de production pour chaque fichier
main.o : main.c code.c code.h
	$(CC) main.c -c $(CFLAGS)
code.o : code.c code.h
	$(CC) code.c -c $(CFLAGS)
# regle de suppression des fichiers
clean:
	rm -rf prog *.o
