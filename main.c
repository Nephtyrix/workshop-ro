#include "graphe.h"
#include<stdio.h>
#include<graph.h>
#include<stdlib.h>

int main()
{
	int nbc;
	couleur *cl;
	graphe G = LireGraphe(stdin);
	AfficherGraphe(G,stdout);
	InitialiserGraphique();
	CreerFenetre(0,0,600,600);
	cl=ColorierGraphe( G, &nbc);
	DessinerGrapheCouleur(G, 300, 300, 200, 10, cl);
	Touche();
	FermerGraphique();
	free(cl);
}

