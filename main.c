#include<limits.h>
#include "tree.h"
#include "scan.h"
#include "save.h"




int main(int argc, char **argv){

    char *home = getenv("HOME");
    
    strcat(home,"/.filescanner");

    char filename[PATH_MAX];
    char cwd[PATH_MAX];
    char filetosave[PATH_MAX];

  
    struct tm *timenow;

    time_t now = time(NULL);
    timenow = gmtime(&now);

    strftime(filename, sizeof(filename), "/%Y-%m-%d_%H:%M:%S.scan", timenow);

   
    
  
    int opt = 0;
    

    while((opt = getopt(argc, argv, "o::si::")) != -1){
        switch (opt){
            
            case 'o':
                if (optind < argc && optind > 0 && *argv[optind] != '-') {
                    strcpy(filetosave, argv[optind]);
                   
                    break;
                }
                else{
                    mkdir(home,0700);
                    strcat(home,filename);
                    strcpy(filetosave,home);
                    fopen(filetosave,"w+");
                    break;
                }

            case 'i':
                if (optind < argc && optind > 0 && *argv[optind] != '-') {
                    s_directory *result  = process_dir(argv[optind]);
                    
                    save_to_file(result,filetosave);
                    clear_subdirs(result);
                    break;
                }
                else{
                   
                    s_directory *result  = process_dir(getcwd(cwd,PATH_MAX));
                  
                    save_to_file(result,filetosave);
                    clear_subdirs(result);
                    break;
                }


        } 
      
    }

}