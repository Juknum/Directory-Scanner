OBJ = objects
C = c_files
CFLAGS =  -W -Wall -pedantic -lcrypto -lssl

main: $(OBJ)/main.o $(OBJ)/scan.o $(OBJ)/save.o $(OBJ)/tree.o $(OBJ)/md5sum.o
	gcc -o $@ $^ $(CFLAGS)

$(OBJ)/%.o: $C/%.c
	gcc -c $< -o $@ $(CFLAGS)
