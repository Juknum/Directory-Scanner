#ifndef _SCAN_H
#define _SCAN_H

#include <stdint.h>
#include <linux/limits.h>
#include <sys/types.h>
#include "openssl/md5.h"

typedef enum {DIRECTORY, REGULAR_FILE, OTHER_TYPE} e_type;

typedef struct _file {
	e_type file_type;
	char name[FILENAME_MAX+1];
	time_t mod_time;
	uint64_t file_size;
	u_char md5sum[MD5_DIGEST_LENGTH];
	struct _file *next_file;
} s_file;

typedef struct _directory {
	char name[FILENAME_MAX+1];
	time_t mod_time;
	struct _directory *subdirs;
	s_file *files;
	struct _directory *next_dir;
} s_directory;

s_directory *process_dir(char *path);
s_file *process_file(char *path, bool is_regular);


#endif
