# PROJET LP25 - P21

## Utilisations du programme

### Compilation
```shell
$ make
```

### Options disponibles
```sh
	-o	:	Save file location, default: ~/.filescanner/year-month-day-H:M:S.scan
	-s	:	Activate MD5 sum, disabled by default
	-i	:	Directory to scan, "." by default.
```

### Exemples
```sh
$ ./projet.exe -s
$ ./projet.exe -i dirtest -s
$ ./projet.exe -o save.scan -i dirtest -s
```

### Contenu d'un .scan:
Avec `./projet.exe -i dirtest -s`:

```txt
0	2021-06-15-11:05:23	dirtest/
	1	2021-06-13-21:41:15	166985	0c5d4c056d1d6a1	dirtest/source
	1	2021-06-13-21:41:45	5117	daff437b8ee9da9	dirtest/t1.txt
	1	2021-06-14-16:29:42	5983	31d71342e145b8b	dirtest/t2
	1	2021-06-14-16:29:42	5983	31d71342e145b8b	dirtest/t2_2
	1	2021-06-14-16:29:42	5983	31d71342e145b8b	dirtest/t2_3
	1	2021-06-14-16:29:42	5983	31d71342e145b8b	dirtest/t2_3 (copie 2)
	2	2021-06-14-17:18:37	dirtest/l-t2
	2	2021-06-14-17:19:34	dirtest/l-dest
	1	2021-06-15-11:05:23	5983	31d71342e145b8b	dirtest/;;eefôej
	0	2021-06-11-14:33:55	dirtest/d2/
		1	2021-06-13-21:40:12	5	3ed7ebb03bd052a	dirtest/d2/t4
	0	2021-06-14-16:29:42	dirtest/d_1/
		1	2021-06-13-21:39:12	10	e9d86d6e1ca8768	dirtest/d_1/t3.txt
		0	2021-06-11-14:33:55	dirtest/d_1/d_3/
			1	2021-06-13-21:37:37	14	a391a4971d7511e	dirtest/d_1/d_3/t5.txt
			1	2021-06-13-21:38:53	10	1bc45205f529013	dirtest/d_1/d_3/t6
	0	2021-06-14-16:29:42	dirtest/dest/
		1	2021-06-13-21:40:35	11	df2364e4e0a7086	dirtest/dest/t1.txt
		1	2021-06-13-21:40:46	7	5c952ae695a4af3	dirtest/dest/t2
```

---

## Organisation du projet

### Fonctions
> Etat de l'avancée du projet

- [x] `s_directory *process_dir(char *path);`  
    - [x] Need review
    - [x] Done
- [x] `s_file *process_file(char *path);`  
    - [x] Need review
    - [x] Done
- [x] `int save_to_file(s_directory *root, char *path_to_target);`  
    - [x] Need review
    - [x] Done
- [x] `int append_subdir(s_directory *child, s_directory *parent);`  
    - [x] Need review
    - [x] Done
- [x] `int append_file(s_file *child, s_directory *parent);`  
    - [x] Need review
    - [x] Done
- [x] `void clear_files(s_directory *parent);`  
    - [x] Need review
    - [x] Done
- [x] `void clear_subdirs(s_directory *parent);`  
    - [x] Need review
    - [x] Done
- [x] `int main(int argc, char *argv[])`  
    - [x] Need review
    - [x] Done
- [x] `int compute_md5(char *path, unsigned char buffer[])`  
    - [x] Need review
    - [x] Done

### Git

```sh
git clone https://git-info.utbm.fr/lp25p21/projet.git
git checkout bader-constant-gillard-schneider

git pull  # met à jour les fichiers locaux en fonction des fichiers distants
git add * # ajoute tous les changements au futur commit
git commit -m "MESSAGE A CHANGER" # fait un commit des changements
git push -u origin bader-constant-gillard-schneider # envoi les changements sur gitlab

git status # check s'il y a des changements
```

### Commentaires:
> Petite convention d'écriture d'un commentaire de fonction

```C
/**
 * Description de la fonction
 * @authors la ou les personnes qui ont codé la fonction
 * @param nom_du_parametre description du paramettre
 * @return description de la valeur retournée (ne pas mettre cette ligne si void)
 */
TypeDuRetour nom_de_la_fonction(TypeDuParametre nom_du_paramatre) {
  return 4;
}
```