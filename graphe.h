#ifndef _GRAPHE_ 
#define _GRAPHE_
#include<stdio.h>
#include<graph.h>

typedef struct _graphe
{
	int ordre; /* nb de sommet */
	int **ma;  /* matrice d'adjacence */
	int oriente; /* 1 => oriente, 0 non oriente */
} * graphe ;

graphe  LireGraphe(FILE * stream); /* lecture depuis un fichier */
void AfficherGraphe(graphe G,FILE * stream);
void DessinerGrapheCouleur(graphe G,int x,int y,int R,int r,couleur * cl);
couleur * ColorierGraphe(graphe G,int * nbc);

#endif
