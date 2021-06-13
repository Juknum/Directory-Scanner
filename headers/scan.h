#ifndef _SCAN_H_
#define _SCAN_H_

#include "./definitions.h"

/**
 * scan le dossier
 * @author Florent
 * @param path chemin du dossier
 * @param doMD5 effectue la somme MD5 si vrai (transmet l'info a process_file uniquement)
 * @return NULL si erreur, sinon le pointeur de la structure qui decrit le dossier
 */
s_directory *process_dir(char *path, bool doMD5);

/**
 * scan le fichier
 * @author Florent
 * @param path chemin du fichier
 * @param doMD5 effectue la somme MD5 si vrai
 * @return NULL si erreur, sinon le pointeur de la structure qui decrit le fichier
 */
s_file *process_file(char *path, bool doMD5);

/**
 * Cherche le nom dans fichier, dossier a partir de son chemin
 * @author Florent
 * @param path chemin du fichier, dossier
 * @return le nom 
 */
char * recuperation_nom(char * path);

#endif //_SCAN_H_ 
