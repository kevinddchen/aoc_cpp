CC = g++
CFLAGS = -I./src/include -Wall -std=c++20 -O3
SRC = ./src/aoc
BIN = ./bin
DATA = ./data

$(DATA)/%.txt:
	@if [ ! -e $@ ]; then\
		echo "ERROR: Missing puzzle input '$@'";\
		echo "       Copy and paste from: https://adventofcode.com/";\
		exit 1;\
	fi

$(BIN)/%: $(SRC)/%.cpp $(DATA)/%.txt
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) $<

.PHONY: clean
clean:
	rm -rf $(BIN)
