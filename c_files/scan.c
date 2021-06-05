#include "../include/scan.h"


s_directory *process_dir(char *path)
{

  s_directory* mainDir = (s_directory*)malloc(sizeof(s_directory));
  strcpy(mainDir->name,path);

  struct dirent* file = NULL;

  DIR* dir = opendir(path);
  if(!dir)
  {
      perror("ERROR");
      return NULL;
  }

    char* tmpPath = (char*)malloc(strlen(path+1)*sizeof(char));
    strcpy(tmpPath,path);


    while( (file = readdir(dir)) != NULL)
    {
      strcpy(tmpPath,path);
      char* p = catPath(tmpPath,file->d_name);
      tmpPath = realloc(tmpPath,strlen(p+1)*sizeof(char));
      strcpy(tmpPath,p);
      s_file* f = NULL;

      if(strcmp(file->d_name,".") != 0 && strcmp(file->d_name,"..") != 0)
      {
        f = process_file(tmpPath);
        add_files(mainDir,f,file->d_name);
        if((int)file->d_type == 4)
        {
          s_directory* newDir = process_dir(tmpPath);
          add_dir(mainDir,newDir);
        }
      }

    }

    free(tmpPath);
    closedir(dir);
    return mainDir;
}

/******************************************/

s_file *process_file(char *path)
{
  s_file* files = (s_file*)malloc(sizeof(s_file));

  struct stat buf;
  stat(path, &buf);

  if(S_ISDIR(buf.st_mode)) files->file_type = DIRECTORY;
  else if(S_ISREG(buf.st_mode)) files->file_type = REGULAR_FILE;
  else files->file_type = OTHER_TYPE;

  return files;
}

/******************************************/

s_directory* add_files(s_directory* dir,s_file* to_add,char* name)
{
  strcpy(to_add->name,name);
  to_add->next_file = NULL;

  if(!dir->files) dir->files = to_add;
  else
  {
    s_directory* tmp = dir;
    while(tmp->files->next_file != NULL)
      tmp->files = tmp->files->next_file;
    tmp->files->next_file = to_add;
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
