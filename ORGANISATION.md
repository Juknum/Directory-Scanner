# Organisation du projet

## Fonctions
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
- [ ] `int append_subdir(s_directory *child, s_directory *parent);`  
    - [ ] Need review
    - [ ] Done
- [ ] `int append_file(s_file *child, s_directory *parent);`  
    - [ ] Need review
    - [ ] Done
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

## Git

```sh
git clone https://git-info.utbm.fr/lp25p21/projet.git
git checkout bader-constant-gillard-schneider

git pull  # met à jour les fichiers locaux en fonction des fichiers distants
git add * # ajoute tous les changements au futur commit
git commit -m "MESSAGE A CHANGER" # fait un commit des changements
git push -u origin bader-constant-gillard-schneider # envoi les changements sur gitlab

git status # check s'il y a des changements
```

## Commentaire:
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