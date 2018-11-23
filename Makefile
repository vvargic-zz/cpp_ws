CXX = g++
CXXFLAGS = -std=c++11 -I.
DEPS =
OBJ = hello_world.o
BIN = hello_world

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(BIN): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(BIN)

