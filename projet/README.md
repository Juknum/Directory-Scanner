## Utilisation du programme  

**make rdir** : pour compiler le programme  
**./rdir** : pour l'exécuter   

## Arguments optionnels du programme  

"**-o Fichier**" : Pour spécifier le fichier dans lequel la sauvegarde de la liste de l'arborescence se fera   
"**-s**" : Activation calcul MD5 des fichiers  
"**-i Dossier**" : Pour spécifier le dossier à analyser   

## Observation des résultats 

Pour observer la base de donnée :  
**sqlite3 rdir.db**  
**select * from filetable;**  
**Ctrl -d** pour fermer  

Autre manière :   
**cd $HOME/.filscanner/**   
**ls** + Regarder le dernier fichier .scan (celui dont le nom = date est la bonne)   
**cat Nom_fichier.scan**   

## Bibliothèques à installer   

Aucune bibliothèque à installer