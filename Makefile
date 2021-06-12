CC=gcc
CFLAGS=-Wall -O2
OBJ_DIR=objects
BIN_DIR=bin
EXEC=main
MD5_INC=-I$(HOME)/openssl-1.1.1k/include/
MD5_LIB=-L$(HOME)/openssl-1.1.1k/ -lssl -lcrypto

all: $(EXEC)

main: $(OBJ_DIR)/md5sum.o $(OBJ_DIR)/main.o
	$(CC) -o $@ $(CFLAGS) $(OBJ_DIR)/main.o $(OBJ_DIR)/md5sum.o
	
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(MD5_LIB) $(MD5_INC) -c -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)


clean:
	rm -f $(OBJ_DIR)/*.o