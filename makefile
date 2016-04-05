CC=gcc
CCFLAGS=-Wall -Wextra -pedantic -g -O3
BIN=main.exe

SRC=$(wildcard *.c)
OBJ=$(SRC:%.c=%.o)

all: $(OBJ)
	$(CC) -o $(BIN) $^ $(CCFLAGS)

%.o: %.c stages.h
	$(CC) -o $@ -c $< $(CCFLAGS)

clean:
	rm *.o $(BIN)

