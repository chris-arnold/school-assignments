#da make file
OBJ = testgetopt.o main.o testreaddir.o getFlagInfo.o

testgetopt.o: testgetopt.c testgetopt.h flagstruct.h
	g++ -c -g testgetopt.c

testreaddir.o: testreaddir.c testreaddir.h flagstruct.h getFlagInfo.h
	g++ -c -g testreaddir.c

main.o: main.c testgetopt.h testreaddir.h
	g++ -c -g main.c
	
getFlagInfo.o: getFlagInfo.c getFlagInfo.h
	g++ -c -g getFlagInfo.c

install: ${OBJ}
	g++ ${OBJ} -o myps

clean: 
	rm -f *.o myps
