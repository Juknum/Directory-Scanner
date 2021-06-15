#ifndef MD5SUM_H
#define MD5SUM_H

#include "./definitions.h"

/**
 * @brief Calcule la somme md5 d'un fichier à partir de son chemin
 * @author Antoine
 * @param path chemin vers le fichier cible
 * @param buffer string pour stocker la somme md5 du fichier
 * @return -1 si le fichier ne peut pas être ouvert, 0 si la fonction réussie
 */
int compute_md5(char *path, unsigned char buffer[]);

#endif
