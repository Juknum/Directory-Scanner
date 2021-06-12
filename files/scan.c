#include "scan.h"

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
            strcpy(new_path,"");
            if (snprintf(new_path, strlen(dir_name)+1+getFileNameSize(current_entry->d_name), "%s/%s", dir_name, current_entry->d_name) < MAX_HANDLED_PATH_LENGTH)
            {
                if (lstat(new_path, &current_stat) != -1) 
                {
                    if (S_ISDIR(current_stat.st_mode)) {
                        append_subdir(process_dir(new_path),parent);
                        scan(new_path,process_dir(new_path));
                    }else{
                        append_file(process_file(new_path),parent);
                    }
                }
            }
        }
    }

}

s_directory *process_dir(char *path){
    struct stat buffer;
    s_directory* new_dir=NULL;
    new_dir=(s_directory*)malloc(sizeof(s_directory));
    if (lstat(path, &buffer) == -1) {
        perror("stat");
    }else{
        strcpy(new_dir->name,path);
        new_dir->mod_time=buffer.st_mtime;
    }
    return new_dir;
}

s_file *process_file(char *path){
    struct stat buffer;
    s_file* new_file=NULL;
    new_file=(s_file*)malloc(sizeof(s_file));
    if (lstat(path, &buffer) == -1) {
        perror("stat");
    }else{
        new_file->file_type=buffer.st_mode;
        strcpy(new_file->name,path);
        new_file->mod_time=buffer.st_mtime;
        new_file->file_size=buffer.st_size;
        new_file->next_file = NULL;
    }
    

    /*uint8_t sumbuff[255];
    FILE *f = fopen(path, "rb");
    uint16_t checksum = 0;
    size_t bytes_read = 0;
    while((bytes_read = fread(sumbuff, sizeof(uint8_t),255, f)) > 0) {
        for (size_t i=0; i<bytes_read; ++i)
            checksum = compute_checksum(sumbuff[i], checksum);
    }
    strcpy(new_file->md5sum,checksum);*/

    return new_file;
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