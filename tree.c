#include "tree.h"

/*---------------------------------------------------------*/

int append_subdir(s_directory *child, s_directory *parent)
{
    if (!child || !parent)
    {
        return 1;
    }

    if (!parent->subdirs)
    {
        parent->subdirs = child;
        return 0;
    }
    
    s_directory * tmp = parent->subdirs;
    while (tmp->next_dir != NULL) {
        tmp = tmp->next_dir;
    }
    tmp->next_dir = child;


    /*s_directory *test = parent->subdirs;

    while (test != NULL)
    {
        printf("%s -> \n ", test->name);
        test = test->subdirs;
    }*/
    

    return 0;

}
    

/*---------------------------------------------------------*/

int append_file(s_file *child, s_directory *parent)
{
    if (!child || !parent)
    {
        return 1;
    }

    if (!parent->files)
    {
        parent->files = child;
        return 0;
    }
    s_file *tmp = parent->files;
    while (tmp->next_file != NULL) {
        tmp = tmp->next_file;
    }
    tmp->next_file = child;
  
    return 0;
}

/*---------------------------------------------------------*/

void clear_files(s_directory* parent)
{
    if (parent == NULL)
    {
        return;
    }

    s_file * tmp = NULL;
    while (parent->files != NULL)
    {
        tmp = parent->files->next_file;
        free(parent->files);
        parent->files = tmp;
    }
}

/*---------------------------------------------------------*/

void clear_subdirs(s_directory* parent)
{
    if (parent == NULL)
    {
        return;
    }
    clear_files(parent);
    if (parent->subdirs != NULL)
    {
        while (parent->subdirs->next_dir != NULL)
        {
            clear_subdirs(parent->subdirs->next_dir);
        }
        clear_subdirs(parent->subdirs);        
    }
   
  
    free(parent);
}

