
oneline.o: oneline.cpp oneline.h
	g++ -c -g oneline.cpp
main.o: main.cpp oneline.h
	g++ -c -g main.cpp

install: oneline.o main.o
	g++ main.o oneline.o -o runme

clean:
	rm -f *.o runme
