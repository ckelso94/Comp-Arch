CC=gcc
CCFLAGS=-Wall -Wextra -pedantic -g
BIN=main.exe

SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)

all: $(OBJ)
	$(CC) -o $(BIN) $^ $(CCFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CCFLAGS)

clean:
	rm *.o $(BIN)

