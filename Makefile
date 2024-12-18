CC = g++
CFLAGS = -I./src/include -Wall -std=c++20 -O2
SRC = ./src/aoc
BIN = ./bin

$(BIN)/%: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) $^

.PHONY: clean
clean:
	rm -rf $(BIN)
