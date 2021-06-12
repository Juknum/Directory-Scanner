#ifndef SAVE_H
#define SAVE_H

#include "./definitions.h"

/**
 * Ouvre le fichier donné par "path_to_target", écris l'arborescence depuis le dossier "root"
 * @author Julien
 * @param root dossier racine depuis laquelle la sauvegarde s'effectue
 * @param path_to_target chemin du fichier vers lequel enregistrer
 * @param nb_tabs nombre de tabulation pour l'indentation (utilisé pour la récursivité)
 * @param path_to_current_dir chemin du dossier racine (s'incrémente des sous-fichiers/sous-dossiers pendant la récursivité)
 * @return -1 si le fichier ne peut pas être ouvert, 0 si la fonction réussie
 */
int save_to_file(s_directory *root, char *path_to_target, int nb_tabs, char *path_to_current_dir);

/**
 * Modifie le buffer pour être une string contenant l'ensemble des infos nécessaires à sauvegarder
 * @author Julien
 * @param dir dossier dont on veut les infos
 * @param path_to_parent_dir chemin d'accès au dossier (sans le dossier)
 * 
 * TODO: faire de l'allocation dynamique pour le buffer (256 char c'est peu)
 */
char* string_builder_of_dir(s_directory dir, char *path_to_parent_dir);

/**
 * Modifie le buffer pour être une string contenant l'ensemble des infos nécessaires à sauvegarder
 * @author Julien
 * @param file fichier dont on veut les infos
 * @param path_to_parent_dir chemin d'accès au fichier (sans le fichier)
 *
 * TODO: faire de l'allocation dynamique pour le buffer (256 char c'est peu)
 */
char* string_builder_of_file(s_file file, char *path_to_parent_dir);

#endif