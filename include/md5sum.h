#ifndef MD5SUM_HEADER
#define MD5SUM_HEADER
#include <stdbool.h>
#include <stdio.h>
#include <openssl/md5.h>

//Generates the MD5 sum of a file and store it in a buffer
int compute_md5(char *path, unsigned char buffer[]);

//converts an MD5 string into hexa, placing it into an array
void md5_to_hexa(unsigned char md5_array[], char* md5_old);

#endif