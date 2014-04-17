#omment in the maek file
CXX = g++

install: exe

clean:
	rm -f *.o exe core*

LinkedList.o: LinkedList.cpp LinkedList.h
	${CXX} -c LinkedList.cpp

main.o: main.cpp LinkedList.h
	${CXX} -c -g main.cpp

exe: LinkedList.o main.o
	${CXX}  LinkedList.o main.o -o exe
