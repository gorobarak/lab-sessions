0a: 0a.c LineParser.c
	gcc -g -Wall -m32 -o 0a 0a.c LineParser.c

0c: 0c.c LineParser.c
	gcc -g -Wall -m32 -o 0c 0c.c LineParser.c

0d: 0d.c LineParser.c
	gcc -g -Wall -m32 -o 0d 0d.c LineParser.c

1: 1.c LineParser.c
	gcc -g -Wall -m32 -o 1 1.c LineParser.c


LineParser: LineParser.c
	gcc -g -Wall -m32 -o LineParser LineParser.c

looper: looper.c
	gcc -g -Wall -m32 -o looper looper.c

clean:
	rm -f *.o LineParser looper 0a 0c 0d 1