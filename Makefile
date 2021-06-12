CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -Wno-unused -g
LDFLAGS = -lcrypto
EXEC = projet

$(EXEC): main.o scan.o save.o tree.o md5sum.o
	$(CC) $(LDFLAGS) -o $@ $^

$(DIR_O)%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm *.o
	rm $(EXEC)
