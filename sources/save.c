#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/save.h"

int save_to_file(s_directory *root, char *path_to_target, int nb_tabs, char *path_to_current_dir) {
  FILE *f = fopen(path_to_target, "a");
  if (!f) return -1;

  // ajout du nombre de tabulation nécessaire (indentation)
  char tabs[nb_tabs + 2];
  for (size_t i = 0; i < nb_tabs; i++) tabs[i] = '\t';
  tabs[nb_tabs] = '\0';

  // ajout des info du dossier actuel
  char buffer[256];
  fputs(tabs, f);
  string_builder_of_dir(buffer, *root, path_to_current_dir);
  fputs(buffer, f);
  tabs[nb_tabs] = '\t';
  tabs[nb_tabs + 1] = '\0';

  // écriture des fichiers
  s_file *current_file = root -> files;
  while (current_file != NULL) {
    string_builder_of_file(buffer, *current_file, path_to_current_dir);
    fputs(tabs, f);
    fputs(buffer, f);
    current_file = current_file -> next_file; // fichier suivant
  }

  fclose(f); // on ferme le fichier maintenant car on le réouvre dans la récurrence

  // écriture des dossiers
  s_directory *current_dir = root -> subdirs;
  char next_dir_path[256];
  while (current_dir != NULL) {
    // récurrence /!\
    strcpy(next_dir_path, path_to_current_dir);
    strcat(next_dir_path, "/"); strcat(next_dir_path, current_dir -> name);
    save_to_file(current_dir, path_to_target, nb_tabs + 1, next_dir_path);
    current_dir = current_dir -> next_dir;
  }

  return 0;
}

void string_builder_of_dir(char *buffer, s_directory dir, char *path_to_parent_dir) {
  char time[32];

  // code e_type
  strcpy(buffer, "0"); // dir e_type
  strcat(buffer, "\t");

  // date
  strftime(time, 32, "%Y-%m-%d-%H:%M:%S", localtime(&dir.mod_time));
  strcat(buffer, time); strcat(buffer, "\t");

  // chemin
  strcat(buffer, path_to_parent_dir); strcat(buffer, dir.name);
  strcat(buffer, "/");
}

void string_builder_of_file(char *buffer, s_file file, char *path_to_parent_dir) {
  char time[32];

  // code e_type
  if (file.file_type == REGULAR_FILE) strcpy(buffer, "1"); // file e_type
  else strcpy(buffer, "2");
  strcat(buffer, "\t");

  // date
  strftime(time, 32, "%Y-%m-%d-%H:%M:%S", localtime(&file.mod_time));
  strcat(buffer, time); strcat(buffer, "\t");

  if (file.file_type == REGULAR_FILE) {
    // taille
    strcat(buffer, file.file_size); strcat(buffer, "\t");

    // md5
    strcat(buffer, file.md5sum); strcat(buffer, "\t");
  }

  // chemin
  strcat(buffer, path_to_parent_dir); strcat(buffer, file.name);
}