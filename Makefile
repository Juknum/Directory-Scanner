CC = gcc
CFLAGS = -Wall -Werror -pedantic -ansi
TARGET = arborescence_displayer
STRUCT_FILE = structures.h
OBJ_DIR = objects
BIN_DIR = bin


# Rules

all: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

$(TARGET): $(OBJ_DIR)/save.o $(OBJ_DIR)/md5sum.o $(OBJ_DIR)/scan.o $(OBJ_DIR)/tree.o
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/%.o: %.c %.h $(STRUCT_FILE)
	$(CC) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

$(BIN_DIR):
	mkdir $@

# Phony target

clean:
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(BIN_DIR)
	$(RM) $(BIN_DIR)
	$(RM) $(OBJ_DIR)

run: all
	./$(TARGET)