#include "tree.h"

int append_subdir(s_directory *child, s_directory *parent)
{
    if(parent->subdirs == NULL)
    {
        parent->subdirs = child;
        printf("Added %s to %s\n",child->name,parent->name);
        return 1;
    }
    else
    {
        s_directory* index = (s_directory*)malloc(sizeof(s_directory));
        index = parent->subdirs;
        while(index->next_dir != NULL)
        {
            index = index->next_dir;
        }
        index->next_dir = child;
        printf("Added %s to %s\n",child->name,parent->name);
        return 1;
    }
}

int append_file(s_file *child, s_directory *parent)
{
    if(parent->files == NULL)
    {
        parent->files = child;
        printf("Added %s to %s\n",child->name,parent->name);
        return 1;
    }
    else
    {
        s_file* index = (s_file*)malloc(sizeof(s_file));
        index = parent->files;
        while(index->next_file != NULL)
        {
            index = index->next_file;
        }
        index->next_file = child;
        printf("Added %s to %s\n",child->name,parent->name);

        return 1;
    }
}

void clear_files(s_directory *parent)
{
    if(parent->files != NULL)
    {
        erase_file_data(parent->files);
        printf("Erased files from %s\n",parent->name);
    }
}

void erase_file_data(s_file *parent)
{
    if(parent->next_file != NULL)
    {
        erase_file_data(parent->next_file);
        free(parent->next_file);
    }
    free(parent);
}

void clear_subdirs(s_directory *parent)
{
    if (parent->subdirs != NULL)
    {
        erase_dir_data(parent->subdirs);
        printf("Erased subdirectories from %s\n",parent->name);
    }   
}

void erase_dir_data(s_directory *parent)
{
    if (parent->next_dir != NULL)
    {
        erase_dir_data(parent->next_dir);
    }
    if (parent->subdirs != NULL)
    {
        erase_dir_data(parent->subdirs);
    }
    clear_files(parent);
    free(parent);
}
