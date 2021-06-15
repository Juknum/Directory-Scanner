CFLAGS=-I. -pthread

main.o: main.c scan.h save.h tree.h
	gcc -o main.o -c main.c $(CFLAGS)

scan.o: scan.c scan.h tree.h 
	gcc -o scan.o -c scan.c $(CFLAGS)

tree.o: tree.c tree.h 
	gcc -o tree.o -c tree.c $(CFLAGS)

save.o: save.c save.h 
	gcc -o save.o -c save.c $(CFLAGS)

arbo : main.o tree.o scan.o save.o 
	gcc -o arbo main.o tree.o scan.o save.o 
