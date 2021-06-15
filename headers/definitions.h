#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <linux/limits.h>
#include "./openssl/md5.h"
#include <time.h>

enum type {
  DIRECTORY,
  REGULAR_FILE,
  OTHER_TYPE
};
typedef enum type e_type;

struct _file {
  e_type   file_type;
  char     name[NAME_MAX + 1];
  time_t   mod_time;
  uint64_t file_size;
  u_char   md5sum[MD5_DIGEST_LENGTH]; // md5sum retourne 32 caracteres mais MD5_DIGEST_LENGTH == 16
  struct   _file *next_file;
};
typedef struct _file s_file;

struct _directory {
  char   name[NAME_MAX + 1];
  time_t mod_time;
  struct _directory *subdirs;
  s_file *files;
  struct _directory *next_dir;
};
typedef struct _directory s_directory;

#endif
