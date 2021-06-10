#ifndef _TREE_H_
#define _TREE_H_

#include "scan.h"

/**
 * Libere la memoire du la structure qui decrit le fichier
 * @author Florent
 * @param parent pointeur la structure qui decrit le fichier
 */
void clear_files(s_file *parent);

/**
 * Libere la memoire du la structure qui decrit le dossier
 * @author Florent
 * @param parent pointeur la structure qui decrit le dossier
 */
void clear_subdirs(s_directory *parent);

#endif //_TREE_H_ 
