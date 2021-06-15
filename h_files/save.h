#ifndef SAVE_H
#define SAVE_H

#include "structures.h"

int save_to_file(s_directory *root, char *path_txt, bool md5);

void ecrire_fichiers(s_file* files,FILE* fichier, int tabs, bool md5);

void ecrire_dirs(s_directory* dirs, FILE* fichier, int tabs, bool md5);

void print_tabs(int tabs,FILE* f);

void print_md5sum(unsigned char buff[], FILE* fichier);

#endif
