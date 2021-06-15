#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "openssl/md5.h"
#include "md5.h"
#include <linux/limits.h>



int compute_md5(char *path, unsigned char buffer[]){

    // calcul de la somme md5 d'un fichier 
    // le buffer represente le digest et stocke la somme MD5

    char buf[512];

    //ouverture du fichier en paramètre en lecture seule 
    int file = open(path,O_RDONLY); 

    MD5_CTX c;
    MD5_Init(&c);
    ssize_t bytes;

    //lecture du fichier
    bytes=read(file, buf, 512);   //lit 512 octets dans le fichier désigné par file et les met dans buf.  bytes prend la valeur du nombre d octet lus

    while(bytes > 0) //lecture complète du fichier
        {
                MD5_Update(&c, buf, bytes);   // mise à jour tant que tous les octets n ont pas été lus
                bytes=read(file, buf, 512);   //lit 512 octets dans le fichier désigné par file et les met dans buf.  bytes prend la valeur du nombre d octet lus
        }

    //copie de la somme MD5 dans buffer
    MD5_Final(buffer, &c);

    //fermeture du fichier
    close(file);

}