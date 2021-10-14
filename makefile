CC=gcc
SRC= src/main.c src/stockage.c src/output.c
include = include/structures.h
OBJ=$(SRC:src/.c=src/.o)
FLAGS=-Wall
LIBS= -lm

stokage:    $(OBJ) $(include)
	$(CC) $(FLAGS) -o $@ $(OBJ) $(LIBS)

%.o:	%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o *~ core
