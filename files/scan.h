#ifndef SCAN
#define SCAN

#include "type.h"
#include "tree.h"
#include "md5sum.h"

void scan(char *dir_name,s_directory *parent);

/*
 *  Function that recursivly reads and get the informations of the repository
 *  char* path - string which represents the path to verify
 *  return - s_directory containing the informations of the directory
 */

int getFileNameSize(char* nameFile);

#endif
