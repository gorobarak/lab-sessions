patch: start.o patch.o util.o 
	ld -m elf_i386 start.o patch.o util.o -o patch

start.o: start.s
	nasm -f elf32 start.s -o start.o

util.o: util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o

patch.o: patch.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector patch.c -o patch.o

clean:
	rm -f *.o patch