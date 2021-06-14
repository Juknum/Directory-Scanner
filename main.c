#include "scan.h"
#include "save.h"
#include "tree.h"

bool do_path =false ;
bool do_arborescence =false ;
bool do_md5sum =false ;

int main(int argc, char *argv[]) {

        char path_to_dir[PATH_MAX]; 
        strcpy(path_to_dir, ".");
        char save_path[PATH_MAX];
        strcpy(save_path, " ");
        char *default_save_dir = "./.filescanner";

        int opt = 0;
        while((opt = getopt(argc, argv, "o:i:spa")) != -1) {
                switch (opt) {
                case 'o':
                        strcpy(save_path, optarg);
                        break;
                case 'i':
                        strcpy(path_to_dir , optarg);
                        break;
                case 'a':
                        do_arborescence = true;
                        break;
                case 'p':
                        do_path = true;
                        break;
                case 's':
                        do_md5sum = true;
                        break;
                }
        }
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
        s_directory *root = process_dir(path_to_dir);
        if (save_to_file(root, save_path, path_to_dir) == 0){
                printf ("File saved to %s\n\n", save_path);
        }else{
                printf ("File couldn't be saved\n\n");
        }
        clear_subdirs(root);
        return 0;
}

