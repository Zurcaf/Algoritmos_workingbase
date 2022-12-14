CFLAGS= -Wall -std=c99 -O3

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
SUBMITNAME = ProjetoAED

BINDIR =
BIN = wrdmttns

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	

