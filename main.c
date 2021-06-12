#include "md5sum.h"
#include "tree.h"
#include "save.h"
#include "scan.h"

int main(int argc, char* argv[]){
    printf("Hello World!");
	int a ;
	unsigned char buffer [2048];
	a = md5sum("texte.txt", buffer);
   return 0;
}