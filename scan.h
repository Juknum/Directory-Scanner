#ifndef SCAN
#define SCAN

#define MAX_HANDLED_PATH_LENGTH 4096

#include "type.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void my_find(char *needle, char *haystack);
#endif