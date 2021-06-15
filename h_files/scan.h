#ifndef SCAN_H
#define SCAN_H

#include "structures.h"
#include "../h_files/tree.h"

typedef enum {FALSE,TRUE} Bool;

s_directory *process_dir(char *path, bool md5);

s_file *process_file(char *path, bool md5);

char* concat(char* dir,char* file);

char* getFileName(char* path);

#endif
