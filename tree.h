#include "scan.h"
#ifndef TREE_HEADER
#define TREE_HEADER


/**
 * @brief : Ajoute un dossier en queue de la liste des sous-dossiers du dossier parent.
 *
 * @param child : Dossier de type structure s_directory ajout� � la liste.
 * @param parent : Dossier parent de type structure s_directory dont l'arborescence de sous-dossiers est modifi�e.
 * @return int : 1 en cas d'�chec, 0 pour r�ussite.  
 */
int append_subdir(s_directory* child, s_directory* parent);

/**
 * @brief : Ajoute un fichier en queue de la liste des fichiers du dossier parent.
 *
 * @param child : Fichier de type structure s_file ajout� � la liste.
 * @param parent : Dossier parent de type structure s_directory dont l'arborescence de fichiers est modifi�e.
 * @return int : 1 en cas d'�chec, 0 pour r�ussite.
 */
int append_file(s_file* child, s_directory* parent);

/**
 * @brief : Lib�re l'espace m�moire allou� pour le stockage de la liste des fichiers du dossier parent. 
 *
 * @param parent : Dossier parent de type structure s_directory dont la liste de fichiers est supprim�e.
 */
void clear_files(s_directory* parent);

/**
 * @brief : Fonction r�cursive
 * - Lib�re l'espace m�moire allou� pour le stockage de la liste des fichiers du dossier parent.
 * - Appel de cette m�me fonction pour tous les dossiers de la liste de sous-dossiers de parent.
 * - lib�re l'espace m�moire allou� pour le stockage du dossier parent.
 * 
 * @param parent : Dossier parent de type structure s_directory dont la liste de fichiers est supprim�e.
 */
void clear_subdirs(s_directory* parent);

#endif 
