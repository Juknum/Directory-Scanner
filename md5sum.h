#ifndef _md5sum_H
#define _md5sum_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

int md5sum(char* path, unsigned char buffer[]);

#endif
