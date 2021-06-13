#ifndef MD5SUM_H
#define MD5SUM_H

/*
 * Calcule la somme md5 d'un fichier à partir de son chemin (variable path)
 * Stocke la somme md5 du fichier dans le buffer
 */
int compute_md5(char *path, unsigned char buffer[]);

#endif