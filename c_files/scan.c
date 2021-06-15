#include "../h_files/scan.h"

// Cette fonction sert à creer l'adresse du prochian fichier à lire
char* concat(char* dir,char* file)
{
	char* path = (char*)malloc( (strlen(dir)) + strlen(file) + 2);
	strcpy(path,dir);
	strcat(path,"/");
	strcat(path,file);
	path[strlen(path)] = '\0';
	return path;
}

// Cette fonction sert à récuperer le nom d'un fichier par rapport au path entré
char* getFileName(char* path)
{
	char* p = (char*)malloc(strlen(path)+1);
	strcpy(p,path);

	char *tok = strtok ( p, "/");
	char *FileName = (char*)malloc(strlen(tok)+1);
	strcpy(FileName, tok);

	while ( tok != NULL )
	{
		free(FileName);
		FileName = malloc(sizeof(char)*(strlen(tok)+1));
		strcpy(FileName, tok);
		tok = strtok ( NULL, "/" );
	}
	free(p);
	return FileName;
}

// Cette fonction va lire le contenu du directory
s_directory *process_dir(char *path, bool md5)
{
	s_directory* dir = (s_directory*)malloc(sizeof(s_directory));
	dir->files = NULL;
	dir->subdirs = NULL;
	dir->next_dir = NULL;

	struct stat st;
	stat(path, &st);
	dir->mod_time = st.st_mtime;

	char* res = getFileName(path); // On récupère le nom du fichier
	strcpy(dir->name,res); // On l'ajoute à la structure
	free(res);
	struct dirent* dirent = NULL;

	DIR* d = opendir(path); // Ouverture du répertoire
	if(!d)
	{
		perror("ERROR");
		return NULL;
	}

	char* tPath = NULL;

	while((dirent = readdir(d)) != NULL) // Lecture de tout le répertoire
	{
		s_file* f = NULL;
		if(strcmp(dirent->d_name,".") != 0 && strcmp(dirent->d_name,"..") != 0 && strcmp(dirent->d_name,".git") != 0)
		{
			tPath = concat(path,dirent->d_name);
			f = process_file(tPath, md5);
			append_file(f,dir);

			if((int)dirent->d_type == 4) //Recherche du type du fichier
			{
				s_directory* newDir = process_dir(tPath, md5);
				append_subdir(newDir,dir);
			}
			free(tPath);
			tPath = NULL;
		}
	}

	if(d) 
	{
		closedir(d);
	}
	return dir;
}

// Cette fonction va lire le contenu d'un file
s_file *process_file(char *path, bool md5)
{
	s_file* file = (s_file*)malloc(sizeof(s_file));
	file->next_file = NULL;

	char* name = getFileName(path); // On recupere le nom du file
	strcpy(file->name,name); // On le côpie dans sa structure
	free(name);

	struct stat st;
	stat(path, &st);

	if(S_ISDIR(st.st_mode))
	{ 
		file->file_type = DIRECTORY;
	}
	else if(S_ISREG(st.st_mode))
	{
		file->file_type = REGULAR_FILE;
		if(md5) 
		{
			compute_md5(path, file->md5sum);
		}
	}  
	else
	{
		file->file_type = OTHER_TYPE;
		if(md5) 
		{
			compute_md5(path, file->md5sum);
		}
	}


	file->file_size = st.st_size;
	file->mod_time = st.st_mtime;

	return file;
}
