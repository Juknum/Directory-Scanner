#define BUFFER_SIZE 1500
#include "md5sum.h"
//OPENSSL_INCLUDE
//OPENSSL_LIBS

int compute_md5(char *path, unsigned char buffer[])
{
	FILE* f = fopen(path, "rb");
	if (!f) 
	{
		printf("file unavailable!\n");
		return false;
	}
	MD5_CTX ctx;
	MD5_Init(&ctx);
	uint8_t tmp_buffer[BUFFER_SIZE] = {0};
	
	while (!ferror(f))
	{
		size_t length;
		while (!feof(f) && length != 0) 
		{
			length = fread(tmp_buffer, 1, BUFFER_SIZE, f);
			if (length != 0)
			{
				MD5_Update(&ctx, tmp_buffer, length);
			}
		}
		MD5_Final(buffer, &ctx);
		fclose(f);
		return true;
	}
	printf("error encountered while reading file!\n");
	return false;
}

void md5_to_hexa(unsigned char md5_array[], char* md5_old)
{
	for(int n=0; n<MD5_DIGEST_LENGTH; n++)
	{
		sprintf(md5_old+2*n,"%02x", md5_array[n]);
	}
	return;
}

