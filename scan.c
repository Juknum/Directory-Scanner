#include <time.h>
#include <libgen.h>
#include<linux/limits.h>

#include "scan.h"
#include "tree.h"



s_directory *init_dir();
s_file *init_file();




s_directory *process_dir(char *path){
  
    s_directory *dir_struct=init_dir();                                              
    //Getting name value by using basename                                           
    strcpy(dir_struct->name,path);  

    
    //Getting mod_time value by using astat struct and time() method                 
    struct stat attr;                                             
    stat(dir_struct->name,&attr);                                                    
    dir_struct->mod_time=time(&attr.st_mtime);                                       


    DIR *rep ;
    struct dirent *dirent;

    

    rep = opendir(path);
    dirent = readdir(rep);
    
    
    
    char process_path[PATH_MAX];



    while(dirent!=NULL){

         
        switch(dirent->d_type){                                                             
            case DT_DIR:                                                                      
              if(strcmp(dirent->d_name,"..")==0 || strcmp(dirent->d_name,".")==0){             
                break;                                                                        
              }
              else{
                sprintf(process_path,"%s/%s",path,dirent->d_name);
                //printf("%s\n",process_path);
                append_subdir(process_dir(process_path),dir_struct);
                break;
              } 
            case DT_REG:

                sprintf(process_path,"%s/%s",path,dirent->d_name);
    
                append_file(process_reg_file(process_path),dir_struct);
               
                break;
            default:
                
                sprintf(process_path,"%s/%s",path,dirent->d_name);
                append_file(process_oth_file(process_path),dir_struct);

        }
          
        dirent = readdir(rep);

       
      }
    closedir(rep);
    
    return dir_struct;
    
          
  


}

s_file *process_reg_file(char *path){

      s_file *file_struct =init_file();

      file_struct->file_type = REGULAR_FILE;
      
      strcpy(file_struct->name,path);

      struct stat st;
      stat(file_struct->name,&st);
      file_struct->file_size=st.st_size;


      return file_struct;
}

s_file *process_oth_file(char *path){

      s_file *file_struct =init_file();
      

      file_struct->file_type = OTHER_TYPE;


      strcpy(file_struct->name,path);

      struct stat st;
      stat(file_struct->name,&st);
      file_struct->file_size=st.st_size;


      return file_struct;
}



















s_file *init_file(){
  s_file *result=malloc(sizeof(*result));
  result->mod_time=0;
  result->file_size=0;
  
  result->next_file=NULL;
  return result;
 
}


s_directory *init_dir(){
  s_directory *result=malloc(sizeof(*result));
  result->subdirs = NULL;
  result->next_dir=NULL;
  result->files=NULL;
  result->mod_time=0;
  return result;
  
}


