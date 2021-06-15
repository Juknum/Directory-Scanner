#ifndef _TREE_H_
#define _TREE_H_

#include "./definitions.h"

/**
 * @brief Libere la memoire de la structure qui decrit le fichier
 * @author Florent
 * @param parent pointeur de la structure qui decrit le fichier
 */
void clear_files(s_file *parent);

/**
 * @brief Libere la memoire de la structure qui decrit le dossier
 * @author Florent
 * @param parent pointeur de la structure qui decrit le dossier
 */
void clear_subdirs(s_directory *parent);

/**
 * @brief Ajoute le répertoire child en tant que sous dossier au répertoire parent (ou à sa descandence)
 * @author Julien
 * @param child répertoire enfant à attaché à parent
 * @param parent répertoire auquel est attaché child
 * @return false si parent est NULL, vrai sinon
 */
bool append_subdir(s_directory *child, s_directory *parent);

/**
 * @brief Ajoute le fichier child au répertoire parent (ou à sa descandence)
 * @author Julien
 * @param child fichier enfant attaché au parent
 * @param parent répertoire auquel est attaché child
 * @return false si parent est NULL, vrai sinon
 */
bool append_file(s_file *child, s_directory *parent);

#endif //_TREE_H_
