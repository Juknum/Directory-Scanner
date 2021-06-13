#define BUFFER_SIZE 1500
#include <string.h>
#include "md5sum.h"
//OPENSSL_INCLUDE
//OPENSSL_LIBS


int compute_md5(char *path, uint8_t buffer[]) 
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

	while (!feof(f)) 
	{
		size_t length = fread(tmp_buffer, 1, BUFFER_SIZE, f);
		if (length != 0)
		{
			MD5_Update(&ctx, tmp_buffer, length);
		} 
		else break;
	}
	MD5_Final(buffer, &ctx);
	md5_to_hexa(buffer);
	return true;
}

void md5_to_hexa(uint8_t md5_array[])
{
    uint8_t sumbuff[16];
    strcpy((char*)sumbuff,(char*)md5_array);
    for (size_t n = 0; n < MD5_DIGEST_LENGTH; n++) 
    {
        sprintf((char*)md5_array, "%02hhx", sumbuff[n]);
    }
    return;
}
