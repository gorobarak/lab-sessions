t1a: start.o t1a.o util.o
	ld -m elf_i386 start.o t1a.o util.o -o t1a

start.o: start.s
	nasm -f elf32 start.s -o start.o

util.o: util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o

t1a.o: t1a.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector t1a.c -o t1a.o

clean:
	rm -f *.o t1a