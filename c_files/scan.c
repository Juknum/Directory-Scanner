#include "../include/scan.h"


s_directory *process_dir(char *path)
{
  s_directory* mainDir = (s_directory*)malloc(sizeof(s_directory));
  mainDir->subdirs = NULL;
  mainDir->next_dir = NULL;

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
        mainDir = add_files(mainDir,f);

        if((int)file->d_type == 4)
        {
          s_directory* newDir = process_dir(tmpPath);
          mainDir = add_dir(mainDir,newDir);
        }
        free(tmpPath);
        tmpPath = NULL;
      }

    }


    closedir(dir);
    return mainDir;
}

/******************************************/

s_file *process_file(char *path)
{
  s_file* files = (s_file*)malloc(sizeof(s_file));
  char buffer[100];
  char* name = getRelativePath(path);
  strcpy(files->name,name);
  free(name);

  struct stat buf;
  stat(path, &buf);

  if(S_ISDIR(buf.st_mode)){
   files->file_type = DIRECTORY;
   
   }
  else if(S_ISREG(buf.st_mode)){
   	files->file_type = REGULAR_FILE;
   	strftime(buffer, 50, "%d/%m/%Y %H:%M:%S",localtime(&buf.st_mtime) );
  	printf("last modification %s\n",buffer);
   }
  else files->file_type = OTHER_TYPE;
  double taille =buf.st_size;
  printf("%.01lf \n",taille);



  return files;
}

/******************************************/

s_directory* add_files(s_directory* dir,s_file* to_add)
{
  to_add->next_file = NULL;

  if(!dir->files) dir->files = to_add;
  else
  {
    s_file* tmp = dir->files;
    while(tmp->next_file != NULL)
      tmp = tmp->next_file;
    tmp->next_file = to_add;
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
  if(!mainDir->subdirs)
  {
    mainDir->subdirs = newDir;
  }
  else{
    s_directory* tmp = mainDir->subdirs;
    while(tmp->next_dir != NULL)
      tmp = tmp->next_dir;
    tmp->next_dir = newDir;
  }
  return mainDir;
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
    newPath = realloc(newPath,strlen(strToken));
    strcpy(newPath,strToken);
    strToken = strtok ( NULL, "/" );
  }

  free(p);
  return newPath;
}
