/**
 * @file structures.h
 * @author Blanchot Lukas, Viala Alexandre, Chaillard Léo, Lignon Thomas
 * @brief All the libraries used in the project and the useful structures are in this file.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef STRUCTURE_HEADER
#define STRUCTURE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/types.h>
#include <openssl/md5.h>
#include <linux/limits.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>
#include <getopt.h>

/**
 * @brief Enum to indicate what type has the file targeted.
 * 
 */
typedef enum {
    DIRECTORY, //!< It is a directory.
    REGULAR_FILE, //!< It is a regualr file.
    OTHER_TYPE //!< It has another type.
} e_type;

/**
 * @brief Structure to stock the content of a file.
 *
 */
typedef struct _file {
    e_type file_type; //!< Type of file.
    char name[NAME_MAX+1]; //!< The basename of the file.
    time_t mod_time; //!< The last date of modification.
    uint64_t file_size; //!< The isize of the file.
    u_char md5sum[MD5_DIGEST_LENGTH]; //!< The md5sum of the file if it is not a directory.
    struct _file *next_file; //!< A pointer on the next file.
} s_file;


/**
 * @brief Structur to stock the content of a directory.
 *
 */
typedef struct _directory {
    char name[NAME_MAX+1]; //!< The basename of the directory.
    time_t mod_time; //!< The last date of modification.
    struct _directory *subdirs; //!< A pointer on an element of a linked list of s_directory.
    s_file *files; //!< A pointer on an element of a linked list of s_file.
    struct _directory *next_dir; //!< A pointer on the next directory.
} s_directory;

#endif
