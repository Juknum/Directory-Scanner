#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

//gcc md5sum.c -lssl -lcrypto -o 

char *md5sum(char* path, unsigned char buffer) {
	int n;
	MD5_CTX c;
	long size;
	char *out = (char*)malloc(33);
	FILE* f  = NULL;
	f= fopen("texte.txt","rb");
	
	fseek(f,0,SEEK_END);
	size = ftell(f);
	
	MD5_Init(&c);

	while (size > 0)
	{
		if (size > 512 )
		{
		MD5_Update(&c,buffer,512);
		}else{
		MD5_Update(&c,buffer,size);
		}
		size -=512;
		//buffer +=512;
	}
	MD5_Final(buffer, &c);
	
	for (n = 0; n < 16; ++n) {
		snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)buffer[n]);
	}
	        printf("%s\n", out);
	
        fclose(f);
    return out;
}