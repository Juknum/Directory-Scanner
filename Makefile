CC= gcc
CFLAGS = -Wall -Werror -ansi -pedantic -std=c99 -g
OBJ = objects
CF = c_files
HF = include
TARGET = database



all: $(OBJ) $(TARGET)

$(TARGET): $(OBJ)/main.o $(OBJ)/$(TARGET).o
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ)/main.o: $(CF)/main.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ)/%.o: $(CF)/%.c $(HF)/%.h
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