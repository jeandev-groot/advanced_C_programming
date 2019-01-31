# Variables
CFLAGS= -Wall -Wextra -pedantic --std=c99
EXEC= run
CC=gcc

# Cibles
$(EXEC):main.o hachage.o tree.o
	$(CC) -o $(EXEC) main.o hachage.o tree.o

main.o: main.c hachage.h tree.h
	$(CC) $(CFLAGS) -c main.c

hachage.o: hachage.c hachage.h
	$(CC) $(CFLAGS) -c hachage.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

clean:
	rm -rf *.o
	rm $(EXEC)