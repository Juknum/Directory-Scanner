CFLAGS=-I. -pthread

main.o: main.c main.h scan.h save.h tree.h debug.h
	gcc -o main.o -c main.c $(CFLAGS)

scan.o: scan.c scan.h main.h tree.h md5sum.h debug.h
	gcc -o scan.o -c scan.c $(CFLAGS)

tree.o: tree.c tree.h debug.h
	gcc -o tree.o -c tree.c $(CFLAGS)

save.o: save.c save.h database.h debug.h
	gcc -o save.o -c save.c $(CFLAGS)

md5sum.o: md5sum.c md5sum.h
	gcc -o md5sum.o -c md5sum.c $(CFLAGS)

debug.o: debug.c debug.h
	gcc -o debug.o -c debug.c $(CFLAGS)

database.o: database.c database.h sqlite3.h scan.h debug.h md5sum.h
	gcc -o database.o -c database.c $(CFLAGS)

sqlite3.o: sqlite3.c
	gcc -o sqlite3.o -c sqlite3.c $(CFLAGS)


rdir: main.o tree.o scan.o save.o database.o sqlite3.o md5sum.o debug.o
	gcc -o rdir main.o tree.o scan.o save.o database.o sqlite3.o md5sum.o debug.o -pthread -ldl -lcrypto -L.

