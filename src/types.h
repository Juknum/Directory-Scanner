/**
 * @file types.h
 * @author Florian Cloarec
 * @brief file that contain all the struct used in this project
 * @version 0.1
 * @date 15 June 2021
 * 
 * @copyright GNU GENERAL PUBLIC LICENSE
 * 
 */

#ifndef LP25_PROJECT_TYPES_H
#define LP25_PROJECT_TYPES_H


/**
 * 
 * @enum e_type
 * @brief possible type for a file
 * 
 * @author Florian CLOAREC
 */
typedef enum {DIRECTORY, REGULAR_FILE, SYMBOLIK_LINK, OTHER_TYPE} e_type;

/**
 * @struct s_file
 * @brief structure for the file and all the data about it
 * 
 * @author Florian CLOAREC
 */
typedef struct _file {
    e_type file_type; /*!< type of the file*/
    char *name; /*!< name of the file*/
    time_t mod_time; /*!< modification time of the file*/
    uint64_t file_size;  /*!< size of the file*/
    unsigned char *md5sum;  /*!< value of the md5sum of the file*/
    struct _file *pointed_file;  /*!< file pointed by the file if it is a soft link*/
    struct _file *next_file;  /*!< next file in the link list of file */
} s_file;


/**
 * @struct s_directory
 * @brief strucrure for a dir and all the data about it and all it's component
 * 
 * @author Florian CLOAREC
 */
typedef struct _directory {
    char *name; /*!< name of the directory */
    time_t mod_time; /*!< modification time of the directory */
    struct _directory *subdirs;  /*!<  list of the subdirs in the directory*/
    s_file *files; /*!< list of the file in the directory*/
    struct _directory *next_dir; /*!< next directory in the list of directory*/
} s_directory;


#endif //LP25_PROJECT_TYPES_H
