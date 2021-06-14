#include "save.h"
#include "scan.h"

// Get the options from the main.c file
extern bool do_arborescence;
extern bool do_path;
extern bool do_md5sum;

// Print the structure into the save file
int save_to_file(s_directory *root, char *path_to_target, char *path_to_dir){
 
    char temp_path_to_dir[PATH_MAX];
    // open or create the save file
    FILE *target_file = fopen(path_to_target, "w");
    if(!target_file){
        printf("File %s couldn't be opened or created\n\n", path_to_target);
		fprintf(stderr, "Error while opening or creating %s\n", path_to_target);
		return -1;
    } 
    // Print the name of the directory to analyse
    fprintf(target_file,"Analisis of : %s\n\n", path_to_dir);
    // Initialize the path to write according to the option slected
    if(do_path){
        sprintf(temp_path_to_dir,"%s/", path_to_dir);
    }else{
        strcpy(temp_path_to_dir, "");
    }
    // Print the subdirs of the directory
    if(root->subdirs){
        print_dir(target_file,root->subdirs, temp_path_to_dir, 0);
    }
    // Print the files of the directory
    if(root->files){
        print_files(target_file, root->files, temp_path_to_dir, 0);
    }
    // We don't directly use the print_dir function in order not to print the next_dir
    fprintf(target_file, "End of the analisis");
    fclose(target_file);
	return 0;
} 

// Print content of the directory structure into the save file
void print_dir(FILE *target_file, s_directory *my_dir, char *path, int depth){
    write_dir_line(target_file, my_dir, path, depth);
	char new_path[PATH_MAX+2];
    // Change the path to write if the option is activated
    if(do_path){
        sprintf(new_path, "%s%s/", path, my_dir->name);
    }else{
        strcpy(new_path, "");
    }
    // Change the depth of the tree structure if the option is activated
    if(do_arborescence){
        depth++;
    }
    // Print the subdirertories if there are some
    if(my_dir->subdirs){
        print_dir(target_file, my_dir->subdirs, new_path, depth);
    }
    // print the files
    if(my_dir->files){
        print_files(target_file, my_dir->files, new_path, depth);
    }
    if(do_arborescence){
        depth--;
    }
    // print the next directory
    if(my_dir->next_dir){
        print_dir(target_file, my_dir->next_dir, path, depth);
    }
}

// Print all the files in a list
void print_files(FILE *target_file, s_file *my_file, char *path, int depth){
    s_file *temp_file = my_file;
    write_file_line(target_file, temp_file, path, depth);
    // Goes through the list write every file description
    while(temp_file->next_file){
        temp_file = temp_file->next_file;
        write_file_line(target_file, temp_file, path, depth);
    }
}

// Write into the target file the a line containing the file's info
void write_file_line(FILE *target_file,s_file *my_file, char *path,int depth){
    if(!my_file){
        return;
    } 
    // Print the tree structure form
    for(int i = 0; i < depth; i++){
        fprintf(target_file,"\t");
    }
    // Get the detail of the modification time of the file
    struct tm* date = localtime(&my_file->mod_time);
    // Print the file info depending on its type
    if(my_file->file_type == REGULAR_FILE){
        fprintf(target_file,"1\t%04d-%02d-%02d-%02d:%02d:%02d\t",date->tm_year+1900,date->tm_mon+1,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec);
        fprintf(target_file,"%ld\t", my_file->file_size);
        // Compute the md5sum if the option is activated 
        if(do_md5sum){
            fprintf(target_file,"%s\t", my_file->md5sum); 
        }
    }else{
        fprintf(target_file,"2\t%04d-%02d-%02d-%02d:%02d:%02d\t",date->tm_year+1900,date->tm_mon+1,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec);
    }
    fprintf(target_file,"%s%s\n",path,my_file->name);
}

// Write into the target file the a line containing the directory's info
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