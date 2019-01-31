//
//  hachage.h
//
//
//
//

#ifndef hachage_h

#define hachage_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 31
#define TAILLE_TABLE_HASH 4999

//cellule d'une epreuve. Pour chaque epreuve on a le score, le scoreDisplay er le rang 
typedef struct epreuve{
    int score;
    char scoreDisplay[40];
    int rank;
}Epreuve;

//cellule pour un athlète
typedef struct Athlete {
    int AthId;
    unsigned char regId;
    unsigned char divId;
    char lastName[80];
    char firstName[80];
    char gender[5];
    signed char age;
    char weight[20];
    char height[20];
    int affiliateId;
    char affiliateName[100];
    int overallScore;
    int overallRank;
    Epreuve e1;
    Epreuve e2;
    Epreuve e2a;
    Epreuve e3;
    Epreuve e4;
    Epreuve e5;
    
}Athlete, *pAthlete;

//cellule de la table de hachage1.chaque cellule de cette table de hachage comprend la clé:identifiant de l'athlète, un athlète et pointe sur le prochain athlète
typedef struct cell{
    char cle[80];
    Athlete athlete;
    struct cell *suiv;
}Cellule, *Ptcellule, *Liste;


//cellule2 de la table de hachage 2. Chaque cellule de table comprend la clé: le nom de l'athlète,un pointeur d'athlète et un pointeur qui pointe sur le prochain athlète
typedef struct cell2{
    char cle[80];
    pAthlete pat;
    struct cell2 *suiv;
}Cellule2, *Ptcellule2, *Liste2;

//Déclaration table des données
typedef char **Tab;

//Déclaration Hashtable avec clé l'ID
typedef Liste Hashtable[TAILLE_TABLE_HASH];

//Déclaration de la Hashtable avec clé le nom de famille
typedef Liste2 Hashtable2[TAILLE_TABLE_HASH];

void init_ht(Hashtable);
void init_ht2(Hashtable2);
void init_donnee(Tab*);
void clear_donnee(Tab);
void ajout_tete(Liste*,Ptcellule);
void ajout_table(Ptcellule,Hashtable);
void ajout_tete2(Liste2*,Ptcellule2);
void ajout_table2(Ptcellule2,Hashtable2);
unsigned int asciis(char*);
int hash(char*);

void rechercheId(Hashtable ,int);
Ptcellule remplirCellule(Tab);
Ptcellule2 remplirCellule2(pAthlete);
void rechercheID(Hashtable, char *);
pAthlete recherche(Cellule *,char *);
void rechercheNom(Hashtable2 , char *);
void desalloc_thash2(Hashtable2 );
void desalloc_thash(Hashtable );
void desallocation2( Cellule2 **);
void desallocation( Cellule **);

void collisions(Hashtable );
int taille(Liste );

#endif /* hachage_h */

