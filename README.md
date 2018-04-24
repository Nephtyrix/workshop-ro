# Workshop-ro

Développement en C de l'algorithme de Welsh et Powell.

## Installation

Récupérez l'archive de la bibliothèque graphique. 
Après avoir désarchiver, lancer le script configure pour préparer la compilation et l'installation :

```
./configure --prefix=/usr --disable-exemples
```

Important La librairie dépend de la librairie X11 qui doit être installée préalablement et optionnellement de la librairie XPM.

Lancez la commande 
```
make
```
pour la compilation et 
```
make install
```
pour l'installation. (sudo possible si erreurs)
Lancez 
```
make uninstall
```
pour la désinstallation.

## Utilisation 

Editez le fichier "exemple.g" pour faire votre propre matrice si vous le voulez.
Le format d'importation d'un graphe est le suivant :
```
Sommets 6
Oriente 0
A 0 1                                                                           
A 1 2
A 1 3
A 2 5
A 3 5
A 2 3
A 3 4
A 1 5
A 2 4
```

Une fois votre graphe créé, faites :

```
make
```
puis 
```
./main < exemple.g
```
Et voici votre graphe colorié ! 
Dans le terminal vous aurez des informations complémentaire.

# Autres infos : 
	Nous avons personnellement choisis d'utiliser cette méthode de l'algorithme de Welsh et Powell, en faisant le pire parcours possible.
	La méthode est donc celle-ci (en reprenant wikipédia): 

   1. Repérer le degré de chaque sommet.
   2. Ranger les sommets par ordre de degrés décroissants (dans certains cas plusieurs possibilités).
   3. Attribuer au premier sommet (A) de la liste une couleur.
   4. Suivre la liste en attribuant la même couleur au premier sommet (B) qui ne soit pas adjacent à (A).
   5. Suivre (si possible) la liste jusqu'au prochain sommet (C) qui ne soit adjacent ni à A ni à B.
   6. Continuer jusqu'à ce que la liste soit finie.
   7. Prendre une deuxième couleur pour le premier sommet (D) non encore coloré de la liste.
   8. Répéter les opérations 4 à 7.
   9. Continuer jusqu'à avoir coloré tous les sommets.

   Or nous, nous n'avons pas fait l'étape 5, qui demande une optimisation plus poussée, nous avons donc en résultat la plus grosse coloration possible.