CC=gcc
CFLAGS=-Wall
OBJ_DIR=objects/
BIN_DIR=bin/
EXEC=main
MD5_INC=-I$(HOME)/openssl-1.1.1k/include/
MD5_LIB=-L$(HOME)/openssl-1.1.1k/
MD5_FLAGS=-lssl -lcrypto
OBJ_FILES=$(OBJ_DIR)main.o $(OBJ_DIR)md5sum.o $(OBJ_DIR)tree.o $(OBJ_DIR)save.o $(OBJ_DIR)scan.o

all: $(OBJ_DIR) $(EXEC)

$(EXEC):  $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ 
	
$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
# 

$(OBJ_DIR):
	mkdir $(OBJ_DIR)


clean:
	rm -f $(OBJ_DIR)*.o $(EXEC)