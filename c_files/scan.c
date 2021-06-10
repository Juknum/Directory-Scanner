#include "../include/scan.h"


s_directory *process_dir(char *path)
{
  s_directory* mainDir = (s_directory*)malloc(sizeof(s_directory));
  mainDir->files = NULL;
  mainDir->subdirs = NULL;
  mainDir->next_dir = NULL;
  struct stat buf;
  stat(path, &buf);
  mainDir->mod_time = buf.st_mtime;

  char* res = getRelativePath(path);
  strcpy(mainDir->name,res);
  free(res);
  struct dirent* file = NULL;

  DIR* dir = opendir(path);
  if(!dir)
  {
      perror("ERROR");
      return NULL;
  }

    char* tmpPath = NULL;

    while( (file = readdir(dir)) != NULL)
    {
      s_file* f = NULL;
      if(strcmp(file->d_name,".") != 0 && strcmp(file->d_name,"..") != 0 && strcmp(file->d_name,".git") != 0)
      {
        tmpPath = catPath(path,file->d_name);
        f = process_file(tmpPath);
        append_file(f,mainDir);

        if((int)file->d_type == 4)
        {
          s_directory* newDir = process_dir(tmpPath);
          append_subdir(newDir,mainDir);
        }
        free(tmpPath);
        tmpPath = NULL;
      }

    }

    if(dir) closedir(dir);
    return mainDir;
}

/******************************************/

s_file *process_file(char *path)
{
  s_file* files = (s_file*)malloc(sizeof(s_file));
  files->next_file = NULL;

  char* name = getRelativePath(path);
  strcpy(files->name,name);
  free(name);

  struct stat buf;
  stat(path, &buf);

  if(S_ISDIR(buf.st_mode)) files->file_type = DIRECTORY;
  else if(S_ISREG(buf.st_mode)){
    files->file_type = REGULAR_FILE;
    compute_md5(path, files->md5sum);
  }  else{
    files->file_type = OTHER_TYPE;
    compute_md5(path, files->md5sum);
  }


  files->file_size = buf.st_size;
  files->mod_time = buf.st_mtime;

  return files;
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

char* getRelativePath(char* path)
{
  char* p = (char*)malloc(strlen(path)+1);
  strcpy(p,path);

  char * strToken = strtok ( p, "/" );
  char* newPath = (char*)malloc(strlen(strToken)+1);
  strcpy(newPath ,strToken);

  while ( strToken != NULL )
  {
    free(newPath);
    newPath = malloc(sizeof(char)*(strlen(strToken)+1));
    strcpy(newPath,strToken);
    strToken = strtok ( NULL, "/" );
  }
  newPath[strlen(newPath)] = '\0';
  free(p);
  return newPath;
}
