/**
 * @file save.c
 * @brief source file that contain the implementation of the function in the save part of the project
 * @version 0.1
 * @date 15 June 2021
 * 
 * @copyright GNU GENERAL PUBLIC LICENSE
 * 
 */

#include "include.h"

int save_to_file(s_directory *root, char *path_to_target, const char *current_path) {
    FILE *output = fopen(path_to_target, "w");
    if (!output) {
        fprintf(stderr, "Couldn't open %s!\n", path_to_target);
        return -1;
    }

    int res = save_to_file_recursive(output, root, 0, current_path);

    printf("Directory tree written in %s\n", path_to_target);
    fclose(output);

    return res;
}

int save_to_file_recursive(FILE *output, s_directory *current_dir, int depth, const char *current_path) {
    char tabulations[depth + 2];
    int i = 0;
    for (; i < depth; i++) {
        tabulations[i] = '\t';
    }
    tabulations[i] = '\0';

    fputs(tabulations, output);
    write_directory(output, *current_dir, current_path);
    fputs("\n", output);

    tabulations[i] = '\t';
    tabulations[i + 1] = '\0';
    s_file *current_file = current_dir->files;

    while (current_file != NULL) {
        fputs(tabulations, output);
        write_file(output, *current_file, current_path);
        fputs("\n", output);

        current_file = current_file->next_file;
    }

    s_directory *subdir = current_dir->subdirs;
    while (subdir != NULL) {
        char *new_path = (char *) malloc(strlen(current_path) + strlen(subdir->name) + 2);
        if(new_path == NULL){
            printf("error on malloc");
            exit(0);
        }

        strcpy(new_path, current_path);
        strcat(new_path, "/");
        strcat(new_path, subdir->name);

        if (!save_to_file_recursive(output, subdir, depth + 1, new_path)) {
            return 1;
        }
        subdir = subdir->next_dir;
    }

    return 0;
}

int write_file(FILE *output, s_file file, const char *path_to_parent_dir) {
    char buffer[200] = {0};

    fprintf(output, "%d\t", file.file_type);

    strftime(buffer, 200, "%Y-%m-%d %H:%M:%S\t", localtime(&file.mod_time));
    fputs(buffer, output); //time_t

    sprintf(buffer, "%lu\t", file.file_size);
    fputs(buffer, output); //size
    if (file.md5sum == NULL) {
        fprintf(output, "MD5 NOT COMPUTED");
    } else {
        for (size_t n = 0; n < MD5_DIGEST_LENGTH; n++) {
            fprintf(output, "%02hhx", file.md5sum[n]);
        }
    }

    fputs("\t", output); //md5sum

    fprintf(output, "%s/%s", path_to_parent_dir, file.name); // path

    return 0;
}

int write_directory(FILE *output, s_directory dir, const char *path_to_parent_dir) {
    char buffer[200] = {0};

    fputs("0\t", output); //e_type

    strftime(buffer, 200, "%Y-%m-%d %H:%M:%S\t", localtime(&dir.mod_time));
    fputs(buffer, output); //time_t

    fprintf(output, "%s/", path_to_parent_dir); // path

    return 0;
}

int write_other(FILE *output, s_file file, const char *path_to_parent_dir) {
    char buffer[200] = {0};

    fputs("2\t", output); //e_type

    strftime(buffer, 200, "%Y-%m-%d %H:%M:%S\t", localtime(&file.mod_time));
    fputs(buffer, output); //time_t

    fprintf(output, "%s/%s", path_to_parent_dir, file.name); // path

    return 0;
}

char *generateFileName() {
    char *save_file;
    char *baseOutputDir = ".filescanner/";
    char *baseOutputDirExtension = ".scan";

    // Generating timestamp & formatting in a string
    char buffer[200] = {0};
    time_t timestamp = time(NULL);
    strftime(buffer, 200, "%Y-%m-%d %H:%M:%S", localtime(&timestamp));

    size_t totalLength = strlen(baseOutputDir) + strlen(buffer) + strlen(baseOutputDirExtension);
    save_file = malloc(sizeof(char) * totalLength + 1);
    strcpy(save_file, baseOutputDir);
    strcat(save_file, buffer);
    strcat(save_file, baseOutputDirExtension);

    return save_file;
}
