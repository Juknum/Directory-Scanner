# Projet LP25 Groupe 12

## Description

Ce programme permet de scanner récursivement le contenu d'un répertoire et d'inscrire l'arborescence obtenue dans un fichier.

## Compilation

### Prérequis

La bibliothèque `openssl` doit être installée pour permettre le calcul de la somme MD5.

### Compiler avec make

```bash
make projet
```

## Utilisation

```bash
./projet [options]
```

### Options

* **`-o`**`fichier`	Permet de spécifier le fichier de sauvegarde de l'arborescence. (Par défaut, `~/.filescanner/date.scan` où *date* est au format `yyyy-MM-dd-hh:mm:ss`)
* **`-s`**	Active le calcul des sommes MD5.
* **`-i`**`chemin`	Permet de spécifier le répertoire à scanner. (Par défaut, `"."`)

### Exemple d'utilisation

Enregistrer l'arborescence de `~/dir_test/` dans `arborescence.txt` en incluant la somme MD5 dans les informations sur chaque fichier :

```bash
./projet -o "arborescence.txt" -i "~/dir_test" -s
```

## Auteurs

Ce projet a été réalisé par :

* Loïc François
* Léo Berthet
* Brice Van Aken
* Corentin Ehlinger
