#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <linux/limits.h>
#include "scan.h"


#ifndef _SAVE_H_
#define _SAVE_H_

int save_to_file(s_directory *root, char *path_to_target);


void save_reg_file(s_file *file,char *path_to_target);
void save_oth_type(s_file *file,char *path_to_target);
void save_dir(s_directory *dir,char *path_to_target);
#endif //_SAVE_H_
