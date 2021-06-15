#ifndef _MD5SUM_H
#define _MD5SUM_H

int compute_md5(char *path, unsigned char buffer[]);
void convert_hexa(unsigned char md5[], char md5_hexa);

#endif
