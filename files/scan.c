#include "scan.h"

void scan(char *dir_name,s_directory *parent) {
    DIR *directory = opendir(dir_name);
    if (directory) {
        struct dirent *current_entry;
        struct stat current_stat;
        while ((current_entry = readdir(directory)) != NULL) {
            if (strcmp(current_entry->d_name, ".") == 0 || strcmp(current_entry->d_name, "..") == 0)
                continue;
            char new_path[MAX_HANDLED_PATH_LENGTH];
            if (snprintf(new_path, MAX_HANDLED_PATH_LENGTH, "%s/%s", dir_name, current_entry->d_name) < MAX_HANDLED_PATH_LENGTH) {
                if (lstat(new_path, &current_stat) != -1) {
                    if (S_ISDIR(current_stat.st_mode)) {
                        s_directory *current=process_dir(new_path);
                        append_subdir(current,parent);
                        scan(new_path,current);
                    }else{
                        append_file(process_file(new_path),parent);
                    }
                }
            }
        }
        closedir(directory);
    }else{
        printf("Error scan/scan ! Directory not found.\n");
        free(directory);
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