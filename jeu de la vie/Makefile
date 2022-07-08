# compilateur
CC = gcc
# options 
CFLAGS =  -lSDL2 -lm -g -Wall -Wextra 
# liste des fichiers objets
OBJ = vie.o
# regle de production finale tp :
vie : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o vie  
	rm -rf  *.o
	@echo "Lancer le programme avec  ./vie"
# regle de production pour chaque fichier
vie.o : vie.c vie.h
	$(CC) vie.c -c $(CFLAGS)


# regle de suppression des fichiers
clean:
	rm -rf prog *.o
