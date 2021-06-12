# Projet LP25 Groupe 12

## 1) Le groupe  :

Les membres du groupe sont :
+ Loic François
+ Léo Berthet
+ Brice Van Aken
+ Corentin Ehlinger

## 2) Utilité du programme :

Le programme "projet" permet de scanner récursivement le contenu d'un répertoire et d'inscrire l'arborescence obtenue dans un fichier.

Par défaut le programme scanne le dossier ".", mais il est possible de spécifier le dossier à scanner avec l'option -i.

De même : par défaut le programme inscrit l'arborescence dans un fichier nommé avec la structure suivante : `~/.filescanner/yyyy-MM-dd-hh:mm:ss.scan` situé dans un dossier ` ~/.filescanner` mais il est possible de spécifier ce fichier avec avec l'option -o.

Enfin, il est possible d'activer le calcul des sommes MD5 avec l'option -s.

## 3) Utilisation du programme :

Il suffit de rentrer la commande suivante dans le répertoire où se situe le programme.
```bash
./projet
```
Pour activer le calcul des sommes MD5, il faut ajouter l'option -s sans argument :
```bash
./projet -s
```
Il est aussi possible de spécifier le répertoire à scanner avec l'option -i :
Par exemple, on souhaite scanner le répertoire dont le chemin est `home/dir_test` :
```bash
./projet -i "home/dir_test"
```

De même, il aussi possible de spécifier le fichier dans lequel inscrire l'arborescence avec l'option -o :
Par exemple, on souhaite inscrire l'arborescence dans le fichier dont le chemin est `home/arborescence.txt` :
```bash
./projet -o "home/arborescence.txt"
```

Évidemment, il est possible d'activer toutes les options à la fois :
```bash
./projet -o "home/arborescence.txt" -i "home/dir_test" -s
```
### 4) Informations complémentaires :

Dans le fichier de sortie, lorsque le programme inscrit l'arborescence, il inscrit :
+ Le nom, la taille, la date de modification et la somme MD5 (si activée) de chaque fichier.
+ Le nom et la date de modification de chaque dossier.
+ Le nom, le fichier pointé et la date de modification de chaque lien symbolyque.
+ Le nom et la date de modification des autres types de fichier.