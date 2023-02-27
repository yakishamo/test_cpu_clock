TARGET = main
OBJS = rdtsc.o main.o

.PHONY: clean

$(TARGET): $(OBJS)
	gcc -o $@ $^

rdtsc.o: rdtsc.asm
	nasm -f elf64 -o rdtsc.o rdtsc.asm

main.o: main.c
	gcc -c -o main.o main.c

clean:
	rm *.o
