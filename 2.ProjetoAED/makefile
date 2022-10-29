
CFLAGS= -Wall -std=c99 -g

OBJ = obj
SRC = src
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
SUBMITNAME = ProjetoAED

BINDIR = bin
BIN = $(BINDIR)/wr
SUBMITNAME = wrdmttns

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

wrdmttns: CFLAGS= -Wall -std=c99 -O3
wrdmttns: $(clean)
wrdmttns: $(BIN)



$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJ):
	mkdir -p $(OBJ)

clean:
	rm -r $(BINDIR)/* $(OBJ)/*

submit:
	zip -r $(SUBMITNAME) $(SRC) $(MAKEFILE) $(README)