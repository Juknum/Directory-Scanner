CC= gcc
CFLAGS = -Wall -Werror -ansi -pedantic -std=gnu99 -g -lcrypto -lssl
OBJ = objects
BIN = bin
F = files
TARGET = main



all: $(OBJ) $(BIN) $(BIN)/$(TARGET)

$(BIN)/$(TARGET): $(OBJ)/main.o $(OBJ)/$(TARGET).o $(OBJ)/scan.o $(OBJ)/tree.o $(OBJ)/save.o $(OBJ)/md5sum.o
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ)/main.o: $(F)/main.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ)/%.o: $(F)/%.c $(F)/%.h
	$(CC) -o $@ -c $< $(CFLAGS)

# Phony target

$(OBJ):
	mkdir $(OBJ)

$(BIN):
	mkdir $(BIN)

run: all
	./$(BIN)/$(TARGET) bdd

debug: all
	gdb ./$(BIN)/$(TARGET)

clean:
	$(RM) -r $(OBJ)
	$(RM) -r $(BIN)
	$(RM) -r bdd