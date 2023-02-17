all: exServerSocket exClientSocket sin_nombre

sin_nombre: sin_nombre.c
	gcc -o sin_nombre sin_nombre.c

exServerSocket: exServerSocket.c socketMng.o
	gcc -o exServerSocket exServerSocket.c socketMng.o

exClientSocket: exClientSocket.c socketMng.o
	gcc -o exClientSocket exClientSocket.c socketMng.o

socketMng.o: socketMng.c
	gcc -c socketMng.c

clean: 
	rm -f exServerSocket exClientSocket socketMng.o
