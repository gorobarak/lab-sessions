t1a: start.o t1a.o util.o
	ld -m elf_i386 start.o t1a.o util.o -o t1a

t1b: start.o t1b.o util.o
	ld -m elf_i386 start.o t1b.o util.o -o t1b

2a: start.o 2a.o util.o
	ld -m elf_i386 start.o 2a.o util.o -o 2a

2b: start.o 2b.o util.o
	ld -m elf_i386 start.o 2b.o util.o -o 2b

start.o: start.s
	nasm -f elf32 start.s -o start.o

util.o: util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o

t1a.o: t1a.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector t1a.c -o t1a.o

t1b.o: t1b.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector t1b.c -o t1b.o

2a.o: 2a.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector 2a.c -o 2a.o

2b.o: 2b.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector 2b.c -o 2b.o

clean:
	rm -f *.o t1a t1b o1 2a 2b