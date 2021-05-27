#include "../include/tree.h"
#include <stdlib.h>


int append_subdir(s_directory *child, s_directory *parent)
{
  s_directory* tmp = parent;
  while(tmp->subdirs != NULL)
    tmp = tmp->subdirs->next_dir;
  tmp->subdirs->next_dir = child;
    return 1;
}

int append_file(s_file *child, s_directory *parent)
{
    s_directory* tmp = parent;
    while(tmp->files->next_file != NULL)
      tmp->files = tmp->files->next_file;
    tmp->files->next_file = child;
    return 1;
}

void clear_files(s_directory *parent)
{
  s_file* tmp = NULL;
  while(parent->files != NULL)
  {
    tmp = parent->files->next_file;
    free(parent->files);
    parent->files = tmp;
  }
}

void clear_subdirs(s_directory *parent)
{
  while(parent->subdirs != NULL)
    clear_subdirs(parent->subdirs->next_dir);

  clear_files(parent);
  free(parent->subdirs);
}
