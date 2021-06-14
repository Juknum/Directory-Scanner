/**
 * @file tree.c
 * @author Blanchot Lukas, Viala Alexandre, Chaillard Léo, Lignon Thomas
 * @brief All the functions used to modify the s_directory & s_file structure are here.
 * @version 0.1
 * @date 2021-06-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "../include/tree.h"


int append_subdir(s_directory *child, s_directory *parent)
{
  if(parent != NULL)
  {
    child->next_dir = parent->subdirs;
    parent->subdirs = child;
    return 1;
  }
  return 0;
}

int append_file(s_file *child, s_directory *parent)
{
  if(parent != NULL)
  {
    child->next_file = parent->files;
    parent->files = child;
    return 1;
  }
  return 0;
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
