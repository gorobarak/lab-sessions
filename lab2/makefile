addresses: addresses.c
	gcc -m32 -Wall -g -o addresses addresses.c

task1c: task1c.c
	gcc -m32 -Wall -g -o task1c task1c.c

task1d: task1d.c
	gcc -m32 -Wall -g -o task1d task1d.c

task2a: task2a.c task2b.c
	gcc -m32 -Wall -g -o task2a task2a.c task2b.c

task2b: task2b.c
	gcc -m32 -Wall -g -o task2b task2b.c

task2c: task2c.c task2b.c
	gcc -m32 -Wall -g -o task2c task2c.c task2b.c

menu: menu_map.c task2b.c
	gcc -m32 -Wall -g -o menu menu_map.c task2b.c

clean:
	rm -f *.o addresses