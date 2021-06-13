#include <stdio.h>
#include <openssl/md5.h>
#include "md5sum.h"

int compute_md5(char *path, unsigned char buffer[]){
	MD5_CTX c;
	//initialisation de la fonction MD5 de openssl
    MD5_Init(&c);
    //on définit la taille des parties du fichier lu par le programme
    int chunk = 512;

    //on ouvre le fichier qui se trouve dans path, peu importe son extension
    FILE *file = fopen(path,"rb");

    //si il n'y a pas de fichier alors on arrête
    if (file==NULL) return 0;
    
    //tant qu'on est pas arrivé à la fin du fichier
    while(!feof(file)){
    	//on créé le buffer "temp" avec pour taille chunk
        uint8_t temp[chunk];
        //on lit la taille en octet
        size_t sizeb = fread(temp, sizeof(uint8_t), chunk, file);
        //on met a jour la somme md5 (ajout partie par partie)
        MD5_Update(&c, temp, sizeb);
    }
    //on indique la fin de la somme md5, on l'envoie dans notre buffer
    MD5_Final(buffer, &c);
    //on ferme le fichier
    fclose(file);

    return -1;
}

