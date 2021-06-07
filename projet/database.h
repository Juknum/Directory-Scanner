#ifndef _DATABASE_H
#define _DATABASE_H

#include <stdio.h>
#include <linux/limits.h>
#include "scan.h"

#define DATABASE_NAME "rdir.db"
#define MAX_SQL_SIZE PATH_MAX+200

int open_db();
int insert_file(s_file* file);
int insert_directory(s_directory* directory);
int close_db();

#endif
