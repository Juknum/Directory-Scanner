#ifndef TREE_HEADER
#define TREE_HEADER


#include "structures.h"


/**
 * @brief
 *
 * @param child
 * @param parent
 * @return int
 */
int append_subdir(s_directory *child, s_directory *parent);

/**
 * @brief
 *
 * @param child
 * @param parent
 * @return int
 */
int append_file(s_file *child, s_directory *parent);

/**
 * @brief
 *
 * @param parent
 */
void clear_files(s_directory *parent);

/**
 * @brief
 *
 * @param parent
 */
void clear_subdirs(s_directory *parent);



#endif 
