Dans ce jeu de la vie, on utilise une forme graphique du jeu avec la bibliothèque SDL2.

A noter bien, que la version de jeu de la vie qu'on manipule ici, a une grille de forme torique.
D'abord on initialise la grille, avec des zéros (éléments morts) et on donne la possibilité à l'utilisateur de séléctionner les cellules vivantes à travers des cliques souris.
En tapant sur la clé "Entrée", et après 4 secondes, la procédure de naissance, survie et mort des cellules se déclanche suivant la règle suivante:

-Une cellule vivante ne peut survivre que si elle a un ou deux voisins vivants.
-Une cellule morte ne peut peut naître que si elle a exactement 2 voisins vivants.
Le long du programme, la gestion d'erreur est toujours prise en compte.
A la fin du programme, la fenêtre se ferme proprement (SDL_Quit(), gestion d'évenement...).
