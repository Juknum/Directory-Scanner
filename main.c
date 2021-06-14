#include "scan.h"
#include "save.h"
#include "tree.h"
#include "md5sum.h"

bool do_path =false ;
bool do_arborescence =false ;
bool do_md5sum =false ;

int main(int argc, char *argv[]) {
        // Initialize the default path of the directory to analyse
        char path_to_dir[PATH_MAX]; 
        strcpy(path_to_dir, ".");
        char save_path[PATH_MAX];
        strcpy(save_path, " ");
        char *default_save_dir = "./.filescanner";
        int opt = 0;
        // Check which option is activated
        while((opt = getopt(argc, argv, "o:i:spa")) != -1) {
                switch (opt) {
                // Initialize the path of the save file
                case 'o':
                        strcpy(save_path, optarg);
                        break;
                // Initialize the path of the directory to analyse
                case 'i':
                        strcpy(path_to_dir, optarg);
                        break;
                // print the file using an tree structure
                case 'a':
                        do_arborescence = true;
                        break;
                // Print the path of the files in addition to their name
                case 'p':
                        do_path = true;
                        break;
                // Compute the md5sum of every file
                case 's':
                        do_md5sum = true;
                        break;
                }
        }
        // Initialyse the default path of the save file if it hasn't been
        if(strcmp(save_path, " ") == 0){
                time_t timestamp = time(0);
                struct tm* date = localtime(&timestamp);
                char full_date[20]; 
                sprintf(full_date,"%04d-%02d-%02d-%02d:%02d:%02d",date->tm_year+1900,date->tm_mon+1,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec); 
                sprintf(save_path,"%s/%s.scan", default_save_dir, full_date);
                struct stat *dir_stat = {0};
                if(stat(default_save_dir, dir_stat) == -1){
                        mkdir(default_save_dir, 0777);
                }
        }
        // Save the content of the directory into the memory
        s_directory *root = process_dir(path_to_dir);
        // Print the directory content into the selected file
        if (save_to_file(root, save_path, path_to_dir) == 0){
                printf ("\nFile successfully saved to %s\n", save_path);
                clear_subdirs(root);
                return EXIT_SUCCESS;
        }else{
                printf ("\nFile couldn't be saved\n");
                clear_subdirs(root);
                return EXIT_FAILURE;
        }
}

