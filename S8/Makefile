all: exServerSocket exClientSocket lector_socket escritor_socket

exServerSocket: exServerSocket.c socketMng.o
	gcc -o exServerSocket exServerSocket.c socketMng.o

exClientSocket: exClientSocket.c socketMng.o
	gcc -o exClientSocket exClientSocket.c socketMng.o

socketMng.o: socketMng.c
	gcc -c socketMng.c

lector_socket: lector_socket.c
	gcc -o lector_socket lector_socket.c

escritor_socket: escritor_socket.c
	gcc -o escritor_socket escritor_socket.c

clean: 
	rm -f exServerSocket exClientSocket socketMng.o
