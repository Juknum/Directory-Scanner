CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -Wno-unused -g
LDFLAGS = -lcrypto
EXEC = projet
DIR_O = .objects/

$(EXEC): $(DIR_O)main.o $(DIR_O)scan.o $(DIR_O)save.o $(DIR_O)tree.o $(DIR_O)md5sum.o
	$(CC) $(LDFLAGS) -o $@ $^

$(DIR_O)%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -r $(DIR_O)/*
	rm $(EXEC)
