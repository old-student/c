all: main.o hashset.o
	gcc -std=gnu99 -o main main.o hashset.o

main.o: main.c hashset.h
	gcc -std=gnu99 -c main.c hashset.h

hashset.o: hashset.c hashset.h
	gcc -std=gnu99 -c hashset.c hashset.h

clear:
	rm -f main main.o hashset.o
