CC=g++
CFLAGS=-I. -g -O0
DEPS =
OBJ = hello_world.o
BIN = hello_world

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(BIN)

