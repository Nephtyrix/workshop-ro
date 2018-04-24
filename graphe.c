#include <stdio.h>
#include "graphe.h"

#define BUFFER_LENGTH 10000
#define LF 5 
#include <string.h>
#include<stdlib.h>
#include<graph.h>
#include<math.h>

void LireGrapheErreur(int n, char *s);
void _DessinerFleche(double x,double y,double xx,double yy);
void _DessinerBoucle(double x,double y);

/* Lire un graphe
 * Syntaxe:
 * Une entite par ligne, chaque champ separe par un blanc.
 * Syntaxe volontairement rigide pour simplifier le parsing
 * Ordre :  Sommets entier
 * Orientation : Oriente entier  
 * Arete : A x y 
 */

graphe  LireGraphe(FILE * stream)
{
	char buffer[BUFFER_LENGTH];
	int line_number = 0;
	int n,x,y;
	graphe G;
	int alloue=0;
	while (fgets(buffer, BUFFER_LENGTH, stream)) 
	{
		char s[BUFFER_LENGTH];

		line_number++;
		switch (buffer[0]) 
		{
			case 'S':	
			if (sscanf(buffer, "Sommets %d", &n) < 1) 
			{
				LireGrapheErreur(line_number, buffer);
			} 
			else 
			{
				int i;
				if (!alloue)
				{
					G=(graphe)malloc(sizeof(struct _graphe));
					G->ordre=n;
					G->oriente=0;
					G->ma=(int **) malloc(sizeof(int*)*n);
					for(i=0;i<n;i++) 
					{
						G->ma[i]=(int*)malloc(sizeof(int)*n);
						bzero(G->ma[i],sizeof(int)*n);
						alloue=1;
					}
				}
				else
				{
					fprintf(stderr, "l'ordre a déjà été donné");
					exit(2);

				}
			}
			break;
			case 'O':
			if (sscanf(buffer, "Oriente %d", &n) < 1) 
			{
				LireGrapheErreur(line_number, buffer);
			} 
			else 
			{
				if (alloue)
				{
					G->oriente=n;
				}
				else
				{
					fprintf(stderr, "il faut d'abord le nbr de sommets");
					exit(2);
				}
			}
			break;
			case 'A':
			if (sscanf(buffer, "A %d %d", &x,&y) < 2) 
			{
				LireGrapheErreur(line_number, buffer);
			} 
			else 
			{
				if (alloue)
				{
					G->ma[x][y]++;
					if (!G->oriente) G->ma[y][x]++; 
				}
				else
				{
					fprintf(stderr, "il faut d'abord le nbr de sommets");
					exit(2);
				}

			}
			break;
		}
	}
	return G;
}





void LireGrapheErreur(int n, char *s)
{
	fprintf(stderr, "graphe: bad line type at line %d: %s\n", n, s);
	exit(2);
}

void AfficherGraphe(graphe G,FILE * stream)
{
	int i,j,n;

	fprintf(stream,"ordre du graphe %d\n",G->ordre);
	fprintf(stream,"graphe oriente : %d\n",G->oriente);
	n=G->ordre;
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fprintf(stream," %2d",G->ma[i][j]);
		}
		fprintf(stream,"\n");
	}
}

void DessinerGrapheCouleur(graphe G,int x,int y,int R,int r,couleur * cl)
{
	int n=G->ordre;
	int i,j;
	double * pointsx;
	double * pointsy;	
	pointsx=(double*)malloc(sizeof(double)*n);
	pointsy=(double*)malloc(sizeof(double)*n);

	for (i=0;i<n;i++)
	{
		pointsx[i]=x+R*cos((2*M_PI*i)/n);
		pointsy[i]=x+R*sin((2*M_PI*i)/n);
		ChoisirCouleurDessin(cl[i]);
		RemplirArc(pointsx[i]-r,pointsy[i]-r,2*r,2*r,0,360);
	}
	ChoisirCouleurDessin(CouleurParNom("black"));
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if (G->ma[i][j]) 
			{
				if (i==j) _DessinerBoucle(pointsx[i],pointsy[i]);
				if (G->oriente) 
					_DessinerFleche(pointsx[i],pointsy[i],pointsx[j],pointsy[j]);
				else
					DessinerSegment(pointsx[i],pointsy[i],pointsx[j],pointsy[j]);
			}

		}
	}
	free(pointsx);
	free(pointsy);
}

void _DessinerBoucle(double x,double y)
{
	DessinerArc(x-20,y,40,40,0,360);
}

void _DessinerFleche(double x,double y,double xx,double yy)
{
	double vx,vy;
	double ux,uy;
	double mod;
	double temp;
	ux=xx-x;
	uy=yy-y;
	vx=y-yy;
	vy=xx-x;
	mod = sqrt(vx*vx+vy*vy);
	vx/=mod;
	vy/=mod;
	ux/=mod;
	uy/=mod;


	DessinerSegment(x,y,xx,yy);

	xx=0.75*xx+0.25*x;
	yy=0.75*yy+0.25*y;	
	RemplirTriangle(xx,yy,xx-LF*vx-2*LF*ux,yy-LF*vy-2*LF*uy,xx+LF*vx-2*LF*ux,yy+LF*vy-2*LF*uy);
}

couleur * ColorierGraphe(graphe G,int *nbc)
{
	// On défini des couleurs pour les sommets
	couleur choixCouleur[6];
	choixCouleur[0] = CouleurParNom("red");
	choixCouleur[1] = CouleurParNom("blue");
	choixCouleur[2] = CouleurParNom("green");
	choixCouleur[3] = CouleurParNom("black");
	choixCouleur[4] = CouleurParNom("purple");
	choixCouleur[5] = CouleurParNom("orange");

	// On défini ce qu'est un sommet pour cette fonction
	typedef struct Sommet Sommet;
	struct Sommet {
    	int sommetInitial;    // Numéro du sommet dans la matrice
    	int degre;            // degré du sommet
    	int colorie;          // Si sommet colorié 1 sinon 0
	};
	// Tableau de structure
	Sommet sommet[G->ordre];

	// Tableau des couleurs de chaque sommet pour le retour
	couleur *cl = malloc(sizeof(couleur) * G->ordre);

	// Nombre de sommet coloriés au total
	int nbrColorie = 0;

	// Nombre de couleurs utilisées
	int nbrCouleur = 0;

	// Autres variables;
	int i, j, tmpSommet, tmpDegre;
	int n = G->ordre;
		
	// On initialise notre tableau de structure	
	for (i = 0; i < n; i++)
	{
		sommet[i].sommetInitial = i;
		sommet[i].degre = 0;
		sommet[i].colorie = 0;
	}

	// On calcule le degré de chaque sommet :
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if (G->ma[i][j]) 
			{
				sommet[i].degre++;
			}

		}
	}

	// On tri par ordre décroissant :
	for(i = 0; i < n; i++) {                                                                          
      for(j = i+1; j < n; j++) {                    
          if(sommet[j].degre > sommet[i].degre) {                                                                  
              tmpSommet = sommet[i].sommetInitial;
              tmpDegre = sommet[i].degre;
              sommet[i] = sommet[j];                                                       
              sommet[j].sommetInitial = tmpSommet;
              sommet[j].degre = tmpDegre;                                                 
            }                                                                  
        }                                                                      
    }
	
	// On applique l'algorithme de Welsh et Powell
	while(nbrColorie < G->ordre) {
		for (i=0;i<n;i++) {
			// On applique une couleur au sommet (A) s'il n'est pas déjà colorié
			if (!sommet[i].colorie) {
				cl[i] = choixCouleur[i];
				sommet[i].colorie = 1;
				nbrColorie++;
			}
			// On suit la liste
			for(j=0 ; j<n ; j++) {
				// On trouve un sommet non adjacent
				if (!G->ma[i][j]) {
					// S'il n'est pas encore colorié, on lui attribue la même couleur qu'au sommet (A)
					if (!(sommet[j].colorie)) {
						cl[j] = choixCouleur[i];
						sommet[j].colorie = 1;
						nbrColorie++;
						// Choix personnel, on fait la pire coloration possible
						break;
					}
				}	                                                             
	        }                                                                      
	    }
	}

	// On regarde le nombre de couleurs utilisées
	for (i=0; i<n; i++) {
        for (j=0; j<i; j++)
           if (cl[i] == cl[j])
               break;
        if (i == j)
          nbrCouleur++;
    }

	// Et on l'affiche
	printf("Nombre de couleurs utilisées : %d\n", nbrCouleur);
	
	return cl;
}
