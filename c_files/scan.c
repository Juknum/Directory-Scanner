#include "../include/scan.h"


s_directory *process_dir(char *path)
{
    s_directory* mainDir = (s_directory*)malloc(sizeof(s_directory));
    strcpy(mainDir->name,path);

    s_file* files = NULL;
    struct dirent* file = NULL;

    DIR* dir = opendir(path);
    if(!dir)
    {
      perror("ERROR");
      return NULL;
    }

    char* tmpPath = (char*)malloc(strlen(path+1)*sizeof(char));
    strcpy(tmpPath,path);
    files = process_file(path);
    add_files(mainDir,files);

    while( (file = readdir(dir)) != NULL)
    {

      if((int)file->d_type == 4 && strcmp(file->d_name,".") != 0 && strcmp(file->d_name,"..") != 0)
      {
        s_file* tmpfile = NULL;
        s_directory* newDir = (s_directory*)malloc(sizeof(s_directory));
        strcpy(newDir->name,file->d_name);

        char* p = catPath(tmpPath,file->d_name);
        tmpPath = realloc(tmpPath,strlen(p+1)*sizeof(char));
        strcpy(tmpPath,p);
        tmpfile = process_file(tmpPath);
        add_files(newDir,tmpfile);
        add_dir(mainDir,newDir);


        free(p);
      }

    }

    free(tmpPath);
    closedir(dir);
    return mainDir;
}

/******************************************/

s_file *process_file(char *path)
{
  s_file* files = NULL;
  struct dirent* file = NULL;
  DIR* dir = opendir(path);

  if(!dir) return NULL;

  while( (file = readdir(dir)) != NULL)
  {

    if(strcmp(file->d_name,".") != 0 && strcmp(file->d_name,"..") != 0)
    {
      files = insert_file(files,file->d_name);
      if((int)file->d_type == 4) files->file_type = DIRECTORY;
      if((int)file->d_type == 8) files->file_type = REGULAR_FILE;
      if((int)file->d_type == 10)files->file_type = OTHER_TYPE;
    }
  }

  closedir(dir);
  return files;
}

/******************************************/

s_file* insert_file(s_file* files,char* name)
{
  s_file* tmp = files;
  s_file* f = (s_file*)malloc(sizeof(s_file));
  strcpy(f->name,name);
  f->next_file = NULL;

  if(!files) files = f;
  else{
    while(tmp->next_file != NULL){
      tmp = tmp->next_file;
    }
    tmp->next_file = f;
  }

  return files;
}

/******************************************/

s_directory* add_files(s_directory* dir,s_file* files)
{
  s_directory* tmp = dir;

  if(!dir->files) dir->files = files;
  else{
    while(tmp->files->next_file != NULL){
      tmp->files = tmp->files->next_file;
    }
    tmp->files->next_file = files;
  }

  return dir;
}

/******************************************/

char* catPath(char* dir,char* file)
{
  char* path = (char*)malloc( (strlen(dir)) + strlen(file) + 2);
  strcpy(path,dir);
  strcat(path,"/");
  strcat(path,file);
  path[strlen(path)] = '\0';
  return path;
}

/******************************************/

s_directory* add_dir(s_directory* mainDir,s_directory* newDir)
{
  s_directory* tmp = mainDir;

  newDir->next_dir = NULL;
  newDir->subdirs = NULL;

  if(!mainDir->subdirs) mainDir->subdirs = newDir;
  else{
    while(tmp->subdirs->next_dir != NULL){
      tmp->subdirs = tmp->subdirs->next_dir;
    }
    tmp->subdirs->next_dir = newDir;
  }

  return mainDir;

}
