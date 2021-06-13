#include "save.h"
#include "scan.h"

extern bool do_arborescence;
extern bool do_path;
extern bool do_md5sum;

int save_to_file(s_directory *root, char *path_to_target, char *path_to_dir){
    char full_path[PATH_MAX];
    time_t timestamp = time(0);
    struct tm* date = localtime(&timestamp);
    char full_date[20]; 
    sprintf(full_date,"%04d-%02d-%02d-%02d:%02d:%02d",date->tm_year+1900,date->tm_mon+1,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec); 
    sprintf(full_path,"%s/%s.scan", path_to_target, full_date);
    FILE *target_file = fopen(full_path, "w");
    if(!target_file){
        printf("File %s couldn't be opened or created\n\n", full_path);
		fprintf(stderr, "Error while opening or creating %s\n", full_path);
		return -1;
    } 
    fprintf(target_file,"%s\n\n", full_date);
    fprintf(target_file,"Content of :\n");
    
    if(root->subdirs){
        if(do_path){
			write_dir_line(target_file, root, path_to_dir, 0);
    		fprintf(target_file,"\n\n");
            print_dir(target_file,root->subdirs, path_to_dir, 0);
        }else{
			write_dir_line(target_file, root, "", 0);
            print_dir(target_file,root->subdirs, "", 0);
        }
    }
    if(root->files){
        if(do_path){ 
            print_files(target_file, root->files, path_to_dir, 0);
        }else{
            print_files(target_file, root->files, "", 0);
        }
    }
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
    while(my_dir->subdirs){
        print_dir(target_file, my_dir->subdirs, new_path, depth);
    }
    if(my_dir->files){
        print_files(target_file, my_dir->files, new_path, depth);
    }
    if(do_arborescence){
        depth--;
    }
    while(my_dir->next_dir){
        print_dir(target_file, my_dir->next_dir, path, depth);
    }

}

void print_files(FILE *target_file, s_file *my_file, char *path, int depth){
    write_file_line(target_file, my_file, path, depth);
    while(my_file->next_file){
        print_files(target_file, my_file->next_file, path, depth);
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
        fprintf(target_file,"%" PRIu64 "\t", my_file->file_size);
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