CFLAGS1= -Wall -std=c99 -g
CFLAGS2= -Wall -std=c99 -O3

wordsMutation-O3: wordsMutation.o dicionario.o
	$(CC) $(CFLAGS2) wordsMutation.o dicionario.o -o wordsMutation

gdb: wordsMutation.o dicionario.o
	$(CC) $(CFLAGS1) wordsMutation.o dicionario.o -o wrdmttns

wordsMutations.o: wordsMutation.c wordsMutation.h dicionario.h
	$(CC) $(CFLAGS1) -c wordsMutation.c

dicionario.o: dicionario.c dicionario.h
	$(CC) $(CFLAGS1) -c dicionario.c

