0a: 0a.c 
	gcc -g -Wall -m32 -o 0a 0a.c

0b: 0b.c 
	gcc -g -Wall -m32 -o 0b 0b.c

1: 1.c LineParser.c
	gcc -g -Wall -m32 -o 1 1.c LineParser.c
	
LineParser: LineParser.c
	gcc -g -Wall -m32 -o LineParser LineParser.c

3: 3.c LineParser.c
	gcc -g -Wall -m32 -o 3 3.c LineParser.c

clean:
	rm -f *.o  0a 0b 0d 1 3