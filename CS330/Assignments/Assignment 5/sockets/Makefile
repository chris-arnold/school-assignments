
#da make file
#OBJ = testgetopt.o main.o testreaddir.o getFlagInfo.o

server: socketServer.c socketInclude.h
	gcc socketServer.c socketInclude.h -o server

client: socketClient.c socketInclude.h
	gcc socketClient.c socketInclude.h -o client

clean: 
	rm -f *.o client server
