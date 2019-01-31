//
//  tree.c
//  prog_av
//
//  Created by Brinda Muzakare && Jean de Dieu Nduwamungu.
//

#include "tree.h"

// construction d'un arbre
Tree cons(Athlete* p, Tree left, Tree right) {
    PtNode new = (PtNode)malloc(sizeof(Node));
    new->pa=p;
    new->left=left;
    new->right=right;
    return new;
}

//ajout dans l'arbre par score global trié
void add_score(Tree *p_t,Hashtable ht) {
    //printf("ngaha please\n");
    
    Node *tmpNode;
    Node *tmpTree;
    int i=0;
    // printf("%s\n",ht[i]->athlete.lastName);
    while(i<TAILLE_TABLE_HASH)
    {
        Cellule  *tmp;
        tmp=ht[i];
        
        while(tmp!=NULL){
            tmpTree = *p_t;
            if(tmpTree!=NULL){
                do
                {
                    tmpNode = tmpTree;
                    if((tmp->athlete.overallScore)>(tmpTree->pa->overallScore)){
                        tmpTree = tmpTree->right;
                        if(tmpTree==NULL){
                            tmpNode->right =cons(&(tmp->athlete),NULL,NULL);}
                    }
                    else
                    {
                        tmpTree = tmpTree->left;
                        if(!tmpTree){
                            tmpNode->left =cons(&(tmp->athlete),NULL,NULL);}
                    }
                }while(tmpTree!=NULL);
            }
            else {
                *p_t = cons(&(tmp->athlete),NULL,NULL);
                /*printf("%s->%d\n",(*p_t)->pa->lastName,(*p_t)->pa->overallRank);*/}
   
                tmp=tmp->suiv;
		}
        i++;
        
    }
}

//ajout dans l' arbre par rang global trié 
void add_rang(Tree *p_t,Hashtable ht) {
    
    Node *tmpNode;
    Node *tmpTree;
    int i=0;
    while(i<TAILLE_TABLE_HASH)
    {
        Cellule  *tmp;
        tmp=ht[i];
        // printf("%d\n",tmp->athlete.overallScore);
        while(tmp!=NULL){
            tmpTree = *p_t;
            if(tmpTree!=NULL){
                do
                {
                    tmpNode = tmpTree;
                    if((tmp->athlete.overallRank)>(tmpTree->pa->overallRank)) 
                    {
                        tmpTree = tmpTree->right;
                        if(tmpTree==NULL){
                            tmpNode->right =cons(&(tmp->athlete),NULL,NULL);}
                    }
                    else{
		     
                        tmpTree = tmpTree->left;
                        if(!tmpTree){
                            tmpNode->left =cons(&(tmp->athlete),NULL,NULL);}
		    }
                }while(tmpTree!=NULL);
            }
            else {
                *p_t = cons(&(tmp->athlete),NULL,NULL);
                }
                tmp=tmp->suiv;
        }
        i++;
    }
}

//Affichage d'un noeud de l'arbre
void imprimer(Tree tr,int* k){
    printf("%02d %20s %20s %6d \n",*k,tr->pa->lastName,tr->pa->firstName,tr->pa->overallScore);
}

// fonction pour afficher dans l'ordre decroissant le score
void print_lvr (Tree t,int* i, int* j) {
    if(t==NULL){
        printf("L'arbre est vide!!\n");}
    else if((*i)<=50){
        (*i)++;
        if(t->right!=NULL){
            print_lvr(t->right,i,j);
        }
        imprimer(t,j);
        (*j)++;
        if(t->left!=NULL){
            print_lvr(t->left,i,j);
        }
    }
}

// affichage dans l'ordre croissant du rang selon le genre
void print_lvr_gender (Tree t,int* i, int* j, char* gender) {
    
    if(t==NULL){
        printf("L'arbre est vide!!\n");}
    else if((*i)<=50){
        if (strcmp(t->pa->gender,gender)==0) (*i)++;
        if(t->right!=NULL){
            print_lvr_gender(t->right,i,j,gender);
        }
        if (strcmp(t->pa->gender,gender)==0) {
            imprimer(t,j);
            (*j)++;
        }
        if(t->left!=NULL){
            print_lvr_gender(t->left,i,j,gender);
        }
    }
}

//On affiche le classement des adhérents dans la salle d'ID idSalle
//Affichage ordoonné
void print_lvr_salle (Tree t,int* j, int idSalle) {
    //printf("%c\n",t->pa->gender);
    if(t==NULL){
        printf("L'arbre est vide!!\n");}
    
        if(t->right!=NULL){
            print_lvr_salle(t->right,j,idSalle);
        }
        if (t->pa->affiliateId==idSalle) {
            imprimer(t, j);
            (*j)++;
        }
        if(t->left!=NULL){
            print_lvr_salle(t->left,j,idSalle);
        }
}

//On affiche le classement des adhérents dans les salles situées sur Lille
void print_lvr_lille (Tree t, int* j) {
    //printf("%c\n",t->pa->gender);
    if(t==NULL){
        printf("Votre arbre est vide!!\n");}

        if(t->right!=NULL){
            print_lvr_lille(t->right,j);
        }
        if (t->pa->affiliateId==19413 || t->pa->affiliateId==14534 || t->pa->affiliateId==7775|| t->pa->affiliateId==11610|| t->pa->affiliateId==12105|| t->pa->affiliateId==19352|| t->pa->affiliateId==21303 ) {
           
            imprimer(t,j);
            (*j)++;
        }
        if(t->left!=NULL){
            print_lvr_lille(t->left,j);
        }
}

//Désallouer  l'arbre en le parcourant noeud par noeud
void clearTree(Tree *tree)
{
    Node *tmpTree = *tree;
    
    if(!tree) return;
    
    if(tmpTree->left)  clearTree(&tmpTree->left);
    
    if(tmpTree->right) clearTree(&tmpTree->right);
    
    free(tmpTree);
    
    *tree = NULL;
}
