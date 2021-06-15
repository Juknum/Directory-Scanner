/**
 * @file utils.c
 * @author Florian Cloarec
 * @brief  implementation file of the function who can be util for all part of the project
 * @version 0.1
 * @date 07 June 2021
 * 
 * @copyright GNU GENERAL PUBLIC LICENSE
 * 
 */

#include "include.h"

char* getFilePath(char* fileName, char* dirPath){
    char* filePath = (char*)malloc(sizeof(char)*(strlen(dirPath)+ strlen(fileName) + 2));
    strcpy(filePath, dirPath);
    strcat(filePath, "/");
    strcat(filePath, fileName);

    return filePath;

}

char* getFileName(char* path){

    int lastSlashIndex = 0;
    int pathLen = strlen(path);
    for (size_t i = 0; i < pathLen; i++)
    {
        if (path[i] == '/' && i != pathLen -1){
            lastSlashIndex = i;
        }
    }
    
    char* fileName = (char*)malloc(sizeof(char)*(strlen(path) - lastSlashIndex + 1));

    strcpy(fileName, &path[lastSlashIndex + 1]);

    int finalLen = strlen(fileName);
    if(fileName[finalLen -1] == '/'){
        fileName[finalLen-1] = '\0';
    }

    return fileName;
}