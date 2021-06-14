#include <stdio.h>
#include <sys/types.h>
#include <bsd/md5.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <stdbool.h>


#ifndef _SCAN_H
#define _SCAN_H


typedef enum {DIRECTORY, REGULAR_FILE, OTHER_TYPE} e_type;

// Structure containing info about a file and a pointer to the next file of the list
typedef struct _file {
	e_type file_type;
	char name[FILENAME_MAX+1];
	time_t mod_time;
	uint64_t file_size;
	char md5sum[MD5_DIGEST_LENGTH];
	struct _file *next_file;
} s_file;

// Structure containing info about a directory and a pointer to the next directory of the list
typedef struct _directory {
	char name[FILENAME_MAX+1];
	time_t mod_time;
	struct _directory *subdirs;
	s_file *files;
	struct _directory *next_dir;
} s_directory;

/**
*@param path path to the analysed directory 
*@return structure containing directory's info
**/
s_directory *process_dir(char *path);

/**
*@param path path to the analysed file
*@return structure containing file's info
**/
s_file *process_file(char *path);


#endif