all: prog1 aux prog2 prog3

prog1: prog1.c
	gcc -o prog1 prog1.c

prog2: prog2.c
	gcc -o prog2 prog2.c

prog3: prog3.c
	gcc -o prog3 prog3.c

aux: aux.c
	gcc -o aux aux.c

clean:
	rm -f prog1 aux prog2 prog3
