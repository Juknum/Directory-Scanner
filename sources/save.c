#include "./headers/md5sum.h"
#include "./headers/save.h"
#include "./headers/scan.h"
#include "./headers/tree.h"

#include <linux/limits.h>
#include <time.h>
#include <openssl/md5.h>

typedef enum {
  DIRECTORY,
  REGULAR_FILE,
  OTHER_TYPE
} e_type;

typedef struct _file {
  e_type   file_type;
  char     name[NAME_MAX + 1];
  time_t   mod_time;
  uint64_t file_size;
  u_char   md5sum[MD5_DIGEST_LENGTH];
  struct   _file *next_file;
} s_file;

typedef struct _directory {
  char name[NAME_MAX + 1];
  time_t mod_time;
  struct _directory *subdirs;
  s_file *files;
  struct _directory *next_dir;
} s_directory;

/**
 * Fonction principale
 * @param argc Nombre d'arguments
 * @param argv Tableau des arguemnts
 */
int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
