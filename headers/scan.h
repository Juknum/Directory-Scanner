#ifndef _SCAN_H_
#define _SCAN_H_

#include <linux/limits.h>
#include <time.h>
#include <openssl/md5.h>

typedef enum {DIRECTORY, REGULAR_FILE, OTHER_TYPE} e_type;

typedef struct _file {
    e_type file_type;
    char name[NAME_MAX+1];
    time_t mod_time;
    uint64_t file_size;
    u_char md5sum[MD5_DIGEST_LENGTH];
    struct _file *next_file;
} s_file;

typedef struct _directory {
    char name[NAME_MAX+1];
    time_t mod_time;
    struct _directory *subdirs;
    s_file *files;
    struct _directory *next_dir;
} s_directory;

/**
 * scan le dossier
 * @author Florent
 * @param path chemin du dossier
 * @param nom nom du dossier
 * @return NULL si erreur, sinon le pointeur de la structure qui decrit le dossier
 */
s_directory *process_dir(char *path, char *nom);

/**
 * scan le fichier
 * @author Florent
 * @param path chemin du fichier
 * @param nom nom du fichier
 * @return NULL si erreur, sinon le pointeur de la structure qui decrit le fichier
 */
s_file *process_file(char *path, char *nom);

#endif //_SCAN_H_ 
