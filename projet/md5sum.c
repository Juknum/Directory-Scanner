#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "openssl/md5.h"
#include "md5sum.h"

// calcul de la somme md5 d'un fichier
int compute_md5(char *path, unsigned char buffer[]){
	int n=0;
	MD5_CTX c;
	char buf[512];
	ssize_t bytes;

	int file=open(path,O_RDONLY);
	MD5_Init(&c);
	bytes=read(file, buf, 512);
	while(bytes > 0){
		MD5_Update(&c, buf, bytes);
		bytes=read(file, buf, 512);
    	}
	MD5_Final(buffer, &c);
	close(file);
}

// conversion de la somme md5 en hexadécimal
void convert_hexa(unsigned char md5[], char* md5_hexa){
	int n=0;
	if(md5[0]=='\0'){
		md5_hexa="\0";	
		return;
	}
	for(n=0; n<MD5_DIGEST_LENGTH; n++)
		sprintf(md5_hexa+2*n,"%02x", md5[n]);
	return;
}
