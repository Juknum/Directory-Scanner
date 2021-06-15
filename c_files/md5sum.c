#include "../h_files/md5sum.h"

int compute_md5(char *path, unsigned char buffer[]) 
{
    FILE* file = fopen(path, "rb");
    
    if (!file) 
    {
        printf("Impossible d'ouvrir le fichier %s\n", path);
        return 0;
    }
    MD5_CTX c;

    MD5_Init(&c); // On initialise le MD5
    unsigned char buf[BUFFER_SIZE] = {0};

    while (!feof(file)) 
    {
        ssize_t bytes = fread(buf, 1, BUFFER_SIZE, file);
        while(bytes > 0)
        {
        	MD5_Update(&c, buf, bytes); // On le met à jour tant que 'bytes' n'est pas <= 0)
        	bytes = fread(buf, 1, BUFFER_SIZE, file);
        }
    }

    if (ferror(file)) 
    {
        printf("Erreur lors de la lecture du fichier\n");
        fclose(file);
        return 0;
    } 
    else 
    {
        MD5_Final(buffer, &c); // On insere le MD5 dans le buffer
        return 1;
    }
}

