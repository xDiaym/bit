.PHONY: clean build mandel min minmandel
CC := clang  # GCC has breaking optimizations
FLAGS := -Wall -Werror

clean:
	rm -f ./bit ./dump.bin

build:
	$(CC) main.c -O3 $(FLAGS) -o bit

debug:
	$(CC) main.c -ggdb -Wno-int-converion -o bit

mandel: build
	./but sample/mandel.bf

min:
	$(CC) min.c -O3 -Wno-int-conversion -o bit

minmandel: min
	./bit samples/mandel.bf
