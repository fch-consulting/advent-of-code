CC=gcc
CFLAGS=-I.

part1: day8.part1.c
	$(CC) -o day8 -g day8.part1.c $(CFLAGS)

part2: instruction.c day8.part2.c 
	$(CC) -o day8 -g day8.part2.c instruction.c $(CFLAGS)

run: 
	./day8
