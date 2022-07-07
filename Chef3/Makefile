# compilateur
CC = gcc
# options 
CFLAGS =  -lSDL2 -lSDL2_image -lSDL2_ttf -g -Wall -Wextra 
# liste des fichiers objets
OBJ = main.o markov.o
# regle de production finale tp :
prog : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o prog  
	rm -rf  *.o
	@echo "Lancer le programme avec  ./prog"
# regle de production pour chaque fichier
main.o : main.c markov.c markov.h
	$(CC) main.c -c $(CFLAGS)
markov.o : markov.c markov.h
	$(CC) markov.c -c $(CFLAGS)

# regle de suppression des fichiers
clean:
	rm -rf prog *.o
