#ifndef _SAVE_H_
#define _SAVE_H_

#include "types.h"

int save_to_file(s_directory *root, char *path_to_target);

void print_file(s_file *file, char *path);
void print_dir(s_directory *dir, char *path);

#endif
