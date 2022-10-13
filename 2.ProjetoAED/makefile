CFLAGS1= -Wall -std=c99 -g
CFLAGS2= -Wall -std=c99 -O3

wordsMutation-O3: 0-wordsMutation.o 1-dicionario.o 2-pals.o 3-fileStats.o
	$(CC) $(CFLAGS2) 0-wordsMutation.o 1-dicionario.o 2-pals.o 3-fileStats.o -o wrdmttns
	rm -f *.o wordsMutation

gdb: 0-wordsMutation.o 1-dicionario.o 2-pals.o 3-fileStats.o
	$(CC) $(CFLAGS1) 0-wordsMutation.o 1-dicionario.o 2-pals.o 3-fileStats.o -o wr-gdb
	rm -f *.o wordsMutation




0-wordsMutations.o: 0-wordsMutation.c  0-wordsMutation.h  1-dicionario.h  2-pals.h  3-fileStats.h
	$(CC) $(CFLAGS1) -c 0-wordsMutation.c

1-dicionario.o: 1-dicionario.c  1-dicionario.h
	$(CC) $(CFLAGS1) -c 1-dicionario.c

2-pals.o: 2-pals.c  2-pals.h
	$(CC) $(CFLAGS1) -c 2-pals.c

3-fileStats.o: 3-fileStats.c  3-fileStats.h
	$(CC) $(CFLAGS1) -c 3-fileStats.c




clean: wordsMutation.o
	

