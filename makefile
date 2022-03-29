all: task0

task0: numbers.o main.o add.o
	gcc -g -m32 -Wall -o task0 main.o numbers.o add.o

numbers.o: numbers.c
	gcc -g -m32 -Wall -c numbers.c

main.o: main.c
	gcc -g -m32 -Wall -c main.c

add.o: add.s
	nasm -g -f elf -w+all add.s

clean: rm -f *.o task0