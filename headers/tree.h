#ifndef _TREE_H_
#define _TREE_H_

#include "./definitions.h"

/**
 * Libere la memoire de la structure qui decrit le fichier
 * @author Florent
 * @param parent pointeur de la structure qui decrit le fichier
 */
void clear_files(s_file *parent);

/**
 * Libere la memoire de la structure qui decrit le dossier
 * @author Florent
 * @param parent pointeur de la structure qui decrit le dossier
 */
void clear_subdirs(s_directory *parent);

/**
 * @author Guillaume
 */
int append_subdir(s_directory *child, s_directory *parent);

/**
 * @author Guillaume
 */
int append_file(s_file *child, s_directory *parent);

#endif //_TREE_H_
