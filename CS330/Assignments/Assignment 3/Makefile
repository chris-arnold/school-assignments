#da make file
#OBJ = testgetopt.o main.o testreaddir.o getFlagInfo.o

myshellfunctions.o: myshellfunctions.c myshellfunctions.h
	g++ -c -g myshellfunctions.c


myshell.o: myshell.c myshellfunctions.h
	g++ -c -g myshell.c

install: myshell.o myshellfunctions.o
	g++ myshell.o myshellfunctions.o -o run

clean: 
	rm -f *.o run
