#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "openssl/md5.h"
#include "md5.h"
#include <linux/limits.h>
int main(int argc , char **argv){
    unsigned char buffer;
    compute_md5("/home/ebessah/Bureau/save.scan",buffer);
}
int compute_md5(char *path, unsigned char buffer[]){

    // calcul de la somme md5 d'un fichier 
    // le buffer represente le digest
    //stocke MD5sum
    char buf[512];

        //ouverture fichier  en lecture seule => O_RDONLY
        int file = open(path,O_RDONLY); 

    MD5_CTX c;
        ssize_t bytes;
    MD5_Init(&c);

    //lecture du fichier
        bytes=read(file, buf, 512);   //lit 512 octets dans le fichier désigné par file et les met dans buf.  bytes prend la valeur du nombre d octet lus

        while(bytes > 0) //lecture complète du fichier
        {
                MD5_Update(&c, buf, bytes);
                bytes=read(STDIN_FILENO, buf, 512);   //lit 512 octets dans le fichier désigné par file et les met dans buf.  bytes prend la valeur du nombre d octet lus
        }

        MD5_Final(buffer, &c);

    //fermeture du fichier
        close(file);

        for(int n=0; n<MD5_DIGEST_LENGTH; n++)
                printf("%02x", buffer[n]); //affichage de MD5sum
 
        return 0;
}

