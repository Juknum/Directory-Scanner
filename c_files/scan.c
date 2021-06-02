#include "../include/scan.h"


s_directory *process_dir(char *path)
{
    s_directory* mainDir = (s_directory*)malloc(sizeof(s_directory));
    s_file* files = NULL;
    struct dirent* file = NULL;

    DIR* dir = opendir(path);
    if(!dir)
    {
      perror("ERROR");
      return NULL;
    }

    while( (file = readdir(dir)) != NULL)
    {
      if(strcmp(file->d_name,".") != 0 && strcmp(file->d_name,"..") != 0)
      {
        char* p = catPath(path,file->d_name);
        s_file* tmpfile = process_file(p);
        files = insert_file(files,tmpfile);
        mainDir = add_files(mainDir,files);
        free(tmpfile);
      }

    }
    closedir(dir);
    return mainDir;
}

/******************************************/

s_file *process_file(char *path)
{
  s_file* files = (s_file*)malloc(sizeof(s_file));
  struct dirent* file = NULL;
  DIR* dir = opendir(path);

  if(!dir) return NULL;

  while( (file = readdir(dir)) != NULL)
  {
    strcpy(files->name,file->d_name);
    if((int)file->d_type == 4) files->file_type = DIRECTORY;
    if((int)file->d_type == 8) files->file_type = REGULAR_FILE;
    if((int)file->d_type == 10)files->file_type = OTHER_TYPE;
  }

  closedir(dir);
  return files;
}

/******************************************/

s_file* insert_file(s_file* currFile,s_file* newFile)
{
  s_file* tmp = currFile;

  if(!currFile) currFile = newFile;
  else{
    while(tmp->next_file != NULL){
      tmp = tmp->next_file;
    }
    tmp->next_file = newFile;
  }

  return currFile;
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

char* catPath(char* givenPath,char* fileName)
{
  int length1 = strlen(givenPath);
  int length2 = strlen(fileName);
  char* res = (char*)malloc((length1 + length2 + 1) * sizeof(char));

  strcpy(res,givenPath); //Adding first string to the result

  for(int i = length1,j = 0; (i < (length1 + length2)) && (j<length2);++i, ++j) //Adding second string
    res[i] = fileName[j];
  res[length1 + length2] = '\0'; //Final char

  return res;
}
