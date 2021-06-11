#ifndef _SCAN_H_
#define _SCAN_H_

#include "./definitions.h"


/**
 * scan le dossier
 * @author Florent
 * @param path chemin du dossier
 * @param nom nom du dossier
 * @return NULL si erreur, sinon le pointeur de la structure qui decrit le dossier
 */
s_directory *process_dir(char *path, char *nom);

/**
 * scan le fichier
 * @author Florent
 * @param path chemin du fichier
 * @param nom nom du fichier
 * @return NULL si erreur, sinon le pointeur de la structure qui decrit le fichier
 */
s_file *process_file(char *path, char *nom);

#endif //_SCAN_H_ 
