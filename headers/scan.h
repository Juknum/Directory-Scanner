#ifndef _SCAN_H_
#define _SCAN_H_

#include "./definitions.h"


/**
 * scan le dossier
 * @author Florent
 * @param path chemin du dossier
 * @return NULL si erreur, sinon le pointeur de la structure qui decrit le dossier
 */
s_directory *process_dir(char *path);

/**
 * scan le fichier
 * @author Florent
 * @param path chemin du fichier
 * @return NULL si erreur, sinon le pointeur de la structure qui decrit le fichier
 */
s_file *process_file(char *path);

/**
 * Cherche le nom dans fichier, dossier a partir de son chemin
 * @author Florent
 * @param path chemin du fichier, dossier
 * @return le nom 
 */
char * recuperation_nom(char * path);

#endif //_SCAN_H_ 
