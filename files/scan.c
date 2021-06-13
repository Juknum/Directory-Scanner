#include "scan.h"
#include "md5sum.h"
void scan(char *dir_name,s_directory *parent)
{

    DIR* directory = opendir(dir_name);
    struct dirent* current_entry;
    struct stat current_stat;
    char* new_path = (char*)malloc(sizeof(char));

    while ((current_entry = readdir(directory)) != NULL)
    {
        if (strcmp(current_entry->d_name, ".") != 0 && strcmp(current_entry->d_name, "..") != 0)
        {
            new_path = realloc(new_path,sizeof(char)*(strlen(dir_name)+1+getFileNameSize(current_entry->d_name)));
            
	if (snprintf(new_path, strlen(dir_name)+1+getFileNameSize(current_entry->d_name), "%s/%s", dir_name, current_entry->d_name) < MAX_HANDLED_PATH_LENGTH)
            {
                if (lstat(new_path, &current_stat) != -1) 
                {
                    if (S_ISDIR(current_stat.st_mode)) {
                        s_directory* new_dir=NULL;
                        new_dir=(s_directory*)malloc(sizeof(s_directory));
                        strcpy(new_dir->name,new_path);
                        new_dir->mod_time=current_stat.st_mtime;
			            append_subdir(new_dir,parent);
                        scan(new_path,new_dir);
                    }else{
                        s_file* new_file=NULL;
                        new_file=(s_file*)malloc(sizeof(s_file));
                        if((current_stat.st_mode & S_IFMT) == S_IFREG)
                        {
                            new_file->file_type=1;
                        }
                        else
                        {
                            new_file->file_type=2;
                        }
                        strcpy(new_file->name,new_path);
                        new_file->mod_time=current_stat.st_mtime;
                        new_file->file_size=current_stat.st_size;
                        new_file->next_file = NULL;
                        append_file(new_file,parent);
                        uint8_t sumbuff[MD5_DIGEST_LENGTH];
			compute_md5(new_path,sumbuff);
			strcpy((char*)new_file->md5sum,(char*)sumbuff);
                    }
                }
            }
        }
    }

}



int getFileNameSize(char* nameFile){
    char buffer[1] = {nameFile[0]};
    int i = 1;
    while (i < strlen(nameFile) || strcmp(buffer,"")!=0)
    {
        buffer[0]=nameFile[i];
        i++;
    }
    return i;
}
