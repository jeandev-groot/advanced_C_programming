//
//  tree.h
//  prog_av
//
//  Created by Brinda Muzakare && Jean de Dieu Nduwamungu.
//

#ifndef tree_h
#define tree_h

#include "hachage.h"

/*cellule de l'arbre. Elle est formée d'un pointeur sur un athlète,
un pointeur sur une valeur à gauche de rang inférieur, un pointeur sur valeur droite de rang supérieur */
typedef struct node {
    pAthlete pa;
    struct node *left;
    struct node *right;
} Node, *PtNode, *Tree;



Tree cons(Athlete*, Tree , Tree );
void add_rang(Tree *,Hashtable );
void add_score(Tree *,Hashtable);
void print_lvr (Tree ,int*, int*);
void print_lvr_gender (Tree ,int* ,int*, char* );
void print_lvr_salle (Tree, int*, int);
void print_lvr_lille (Tree , int* );
void clearTree(Tree *);
#endif /* tree_h */
