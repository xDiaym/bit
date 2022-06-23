.PHONY: clean build mandel min minmandel
CC := clang  # GCC has breaking optimizations
SRCS := $(shell find ./src -name '*.c')
INCLUDE := include
FLAGS := -Wall -Werror -I$(INCLUDE)

clean:
	rm -f ./bit ./dump.bin

build:
	$(CC) $(SRCS) -O3 $(FLAGS) -o bit

debug:
	$(CC) $(SRCS) -ggdb $(FLAGS) -o bit

mandel: build
	./bit samples/mandel.bf

min:
	$(CC) min.c -O3 -Wno-int-conversion -o bit

minmandel: min
	./bit samples/mandel.bf
