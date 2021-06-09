CC = gcc
CFLAGS =   -ansi -lcrypto -g -std=c99 -Du_char="unsigned char" -pedantic -Wall -Werror
TARGET = arborescence_displayer
STRUCT_FILE = structures.h
OBJ_DIR = objects
BIN_DIR = bin
CF = c_files
HF = include


# Rules

all: $(OBJ_DIR) $(BIN_DIR) $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ_DIR)/main.o $(OBJ_DIR)/save.o $(OBJ_DIR)/md5sum.o $(OBJ_DIR)/scan.o $(OBJ_DIR)/tree.o
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/main.o: $(CF)/main.c $(HF)/$(STRUCT_FILE)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(CF)/%.c $(HF)/%.h $(HF)/$(STRUCT_FILE)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR):
	mkdir $@

$(BIN_DIR):
	mkdir $@

# Phony target

clean:
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(BIN_DIR)

run: all
	./$(BIN_DIR)/$(TARGET) ~

debug: all
	gdb ./$(BIN_DIR)/$(TARGET)