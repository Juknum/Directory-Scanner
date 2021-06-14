#include "save.h"
#include "scan.h"

extern bool do_arborescence;
extern bool do_path;
extern bool do_md5sum;

int save_to_file(s_directory *root, char *path_to_target, char *path_to_dir){
 
    char temp_path_to_dir[PATH_MAX];
    FILE *target_file = fopen(path_to_target, "w");
    if(!target_file){
        printf("File %s couldn't be opened or created\n\n", path_to_target);
		fprintf(stderr, "Error while opening or creating %s\n", path_to_target);
		return -1;
    } 
    fprintf(target_file,"Analisis of : %s\n\n", path_to_dir);
    if(do_path){
        sprintf(temp_path_to_dir,"%s/", path_to_dir);
    }else{
        strcpy(temp_path_to_dir, "");
    }
    if(root->subdirs){
        print_dir(target_file,root->subdirs, temp_path_to_dir, 0);
    }
    if(root->files){
        print_files(target_file, root->files, temp_path_to_dir, 0);
    }
    fprintf(target_file, "End of the analisis");
    fclose(target_file);
	return 0;
} 

void print_dir(FILE *target_file, s_directory *my_dir, char *path, int depth){
    write_dir_line(target_file, my_dir, path, depth);
	char new_path[PATH_MAX+2];
    if(do_path){
        sprintf(new_path, "%s%s/", path, my_dir->name);
    }else{
        strcpy(new_path, "");
    }
    if(do_arborescence){
        depth++;
    }
    if(my_dir->subdirs){
        print_dir(target_file, my_dir->subdirs, new_path, depth);
    }
    
    if(my_dir->files){
        print_files(target_file, my_dir->files, new_path, depth);
    }
    if(do_arborescence){
        depth--;
    }
    if(my_dir->next_dir){
        print_dir(target_file, my_dir->next_dir, path, depth);
    }
}

void print_files(FILE *target_file, s_file *my_file, char *path, int depth){
    s_file *temp_file = my_file;
    write_file_line(target_file, temp_file, path, depth);
    while(temp_file->next_file){
        temp_file = temp_file->next_file;
        write_file_line(target_file, temp_file, path, depth);
    }
}

void write_file_line(FILE *target_file,s_file *my_file, char *path,int depth){
    if(!my_file){
        return;
    } 
    for(int i = 0; i < depth; i++){
        fprintf(target_file,"\t");
    }
    struct tm* date = localtime(&my_file->mod_time);
    if(my_file->file_type == REGULAR_FILE){
        fprintf(target_file,"1\t%04d-%02d-%02d-%02d:%02d:%02d\t",date->tm_year+1900,date->tm_mon+1,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec);
        fprintf(target_file,"%ld\t", my_file->file_size);
        if(do_md5sum){
            fprintf(target_file,"%s\t", my_file->md5sum); 
        }
    }else{
        fprintf(target_file,"2\t%04d-%02d-%02d-%02d:%02d:%02d\t",date->tm_year+1900,date->tm_mon+1,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec);
    }
    fprintf(target_file,"%s%s\n",path,my_file->name);
}

void write_dir_line(FILE *target_file,s_directory* my_dir, char *path,int depth){
    if(!my_dir){
        return;
    } 
    for(int i = 0; i < depth; i++){
        fprintf(target_file,"\t");
    }
    struct tm* date = localtime(&my_dir->mod_time);
    fprintf(target_file,"0\t%04d-%02d-%02d-%02d:%02d:%02d\t",date->tm_year+1900,date->tm_mon+1,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec);
    fprintf(target_file,"%s%s/\n",path, my_dir->name);
}