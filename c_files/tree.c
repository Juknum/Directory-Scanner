#include "../include/tree.h"
#include <stdlib.h>


int append_subdir(s_directory *child, s_directory *parent)
{
    child->next_dir = parent->subdirs;
    parent->subdirs = child;
    return 1;
}

int append_file(s_file *child, s_directory *parent)
{
    child->next_file = parent->files;
    parent->files = child;
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
  {
    clear_subdirs(parent->subdirs);
    parent->subdirs = parent->subdirs->next_dir;
  }

  clear_files(parent);
  free(parent->subdirs);
  parent->subdirs = NULL;
}
