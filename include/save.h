#ifndef SAVE_HEADER
#define SAVE_HEADER

#include "structures.h"


/**
 * @brief 
 * 
 * @param root 
 * @param path_to_target 
 * @return int 
 */
int save_to_file(s_directory *root, char *path_to_target);


void write_files(s_file* files,FILE* fichier, int tabs);


void write_directories(s_directory* directories, FILE* fichier, int tabs);

void print_tabs(int tabs,FILE* fichier);

void print_md5sum(unsigned char buffer[], FILE* fichier);

#endif