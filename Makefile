CC=gcc
CFLAGS=-Wall
OBJ_DIR=./objects
BIN_DIR=./bin
SRC_BIN=./src
EXEC=main

$(OBJ_DIR)/%.o: $(SRC_BIN)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

all: $(EXEC)

main: $(OBJ_DIR) $(BIN_DIR) $(OBJ_DIR)/main.o $(OBJ_DIR)/md5sum.o $(OBJ_DIR)/scan.o $(OBJ_DIR)/tree.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/save.o
	$(CC) -o $(BIN_DIR)/$@ $(OBJ_DIR)/main.o $(OBJ_DIR)/md5sum.o $(OBJ_DIR)/scan.o $(OBJ_DIR)/tree.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/save.o -lssl -lcrypto

clean:
	rm -f $(BIN_DIR)/main $(OBJ_DIR)/*.o
