#ifndef MD5SUM_HEADER
#define MD5SUM_HEADER
#include <stdbool.h>
#include <stdio.h>
#include <openssl/md5.h>

//Generates the MD5 sum of a file and store it in a buffer
int compute_md5(char *path, uint8_t buffer[]);

//converts an MD5 string into hexa, placing it into an array
void md5_to_hexa(uint8_t md5_array[]);

#endif
