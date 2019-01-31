//  Muzakare Brinda
//  Nduwamungu Jean de Dieu
//  hachage.c
//
//
//
//

#include "hachage.h"

/*Cette fonction prend les caractères de chaque mot passé en fonction,
 additionne leurs code ascii et nous renvoie le résulat */
//unsigned int pour éviter d'avoir des nombres négatifs
unsigned int asciis(char *word)
{
    int i=0;
    unsigned int h=0;
    while(word[i]!='\0')
    {
        h=h+(word[i]-'0');
        i++;
    }
    return h;
}

/*la fonction hash est multipliée par 14071 pour obtenir un nombre
suffisament grand pour pouvoir après avoir appliqué le modulo TAILLE_TABLE_HASH
 on puisse tomber dans une case de la table de hashage valide */
int hash(char *word)
{
    return (asciis(word)*14071 % TAILLE_TABLE_HASH);
}

//Initialisation de la table de Hachage1
void init_ht(Hashtable ht){
    for(int i=0;i<TAILLE_TABLE_HASH;i++){
        ht[i]=NULL;
    }
}
//initialisation de la table de hachage2
void init_ht2(Hashtable2 ht){
    for(int i=0;i<TAILLE_TABLE_HASH;i++){
        ht[i]=NULL;
    }
}


//mettre les donnees dans un tableau
void init_donnee(Tab *tab){
    *tab=malloc(sizeof(char*)*MAX_SIZE);
    for(int i=0;i<MAX_SIZE;i++){
        (*tab)[i]=malloc(sizeof(char)*MAX_SIZE);
    }
}


//supprimer les donnee de la table
void clear_donnee(Tab tab){
    int i;
    for(i=0;i<MAX_SIZE;i++){
        free(tab[i]);
    }
    free(tab);
    
}

//ajout_tete pour insérer un athlète dans la table Hashage 1 qui a comme cle: l'identifiant de l'athlete et la valeur: un apt
void ajout_tete(Liste *pl,Ptcellule pt){
    Liste tmp=pt;
    tmp->suiv=*pl;
    *pl=tmp;
}

//ajout tete pour inserer un athlè dans la  table de Hashage2
void ajout_tete2(Liste2 *pl,Ptcellule2 pt){
    Liste2 tmp=pt;
    tmp->suiv=*pl;
    *pl=tmp;
}




//fonction d'ajout dans la table de hachage1 qui a comme clé: l'identifiant de l'athlète et la valeur: un athlète
void ajout_table(Ptcellule pt, Hashtable ht){
    int position;
    position=hash(pt->cle);
   
    ajout_tete(&(ht[position]),pt);
}
//fonction d'ajout dans  la 2ème table de hachage qui a comme clé: le nom de l'athlète et la valeur:un pointeur d'athlète.
//on lui passe en paramètre un pointeur de cellule2 et la table de hachage pour qu'il lui trouve une position et l'insère dans la table 

void ajout_table2(Ptcellule2 pt, Hashtable2 ht){
    int position;
    position=hash(pt->cle);
    //printf("%d -> %s\n", position,pt->cle);
    ajout_tete2(&(ht[position]),pt);
}
/*fonction pour remplir une cellule. On lui passe en paramètre un tableau qui contient
 toutes les informations pour un seul athlète afin de les stoker dans une cellule.
 le tableau t stocke des char nous avons dû utilisé la fonction atoi pour
 convertir les char en nombre si besoin */
Ptcellule remplirCellule(Tab t){
    Ptcellule tmp;
    
    
    tmp=malloc(sizeof(Cellule));
    
    strcpy(tmp->cle,(t[0]));
    
    tmp->athlete.AthId=atoi(t[0]);
    tmp->athlete.regId=atoi(t[1]);
    tmp->athlete.divId=atoi(t[2]);
    strcpy(tmp->athlete.lastName,(t[3]));
    strcpy(tmp->athlete.firstName,(t[4]));
    strcpy(tmp->athlete.gender,(t[5]));
    tmp->athlete.age=atoi(t[6]);
    strcpy(tmp->athlete.weight,(t[7]));
    strcpy(tmp->athlete.height,(t[8]));
    tmp->athlete.affiliateId=atoi(t[9]);
    strcpy(tmp->athlete.affiliateName,(t[10]));
    tmp->athlete.overallScore=atoi(t[11]);
    tmp->athlete.overallRank=atoi(t[12]);
    tmp->athlete.e1.score=atoi(t[13]);
    strcpy(tmp->athlete.e1.scoreDisplay,(t[14]));
    tmp->athlete.e1.rank=atoi(t[15]);
    tmp->athlete.e2.score=atoi(t[16]);
    strcpy(tmp->athlete.e2.scoreDisplay,(t[17]));
    tmp->athlete.e2.rank=atoi(t[18]);
    tmp->athlete.e2a.score=atoi(t[19]);
    strcpy(tmp->athlete.e2a.scoreDisplay,(t[20]));
    tmp->athlete.e2a.rank=atoi(t[21]);
    tmp->athlete.e3.score=atoi(t[22]);
    strcpy(tmp->athlete.e3.scoreDisplay,(t[23]));
    tmp->athlete.e3.rank=atoi(t[24]);
    tmp->athlete.e4.score=atoi(t[25]);
    strcpy(tmp->athlete.e4.scoreDisplay,(t[26]));
    tmp->athlete.e4.rank=atoi(t[27]);
    tmp->athlete.e5.score=atoi(t[28]);
    strcpy(tmp->athlete.e5.scoreDisplay,(t[29]));
    tmp->athlete.e5.rank=atoi(t[30]);
    return tmp;
}
//fonction pour remplir une cellule2. On lui passe en paramètre un pointeur d'athlète  afin de ne pas dupliquer les données.
Ptcellule2 remplirCellule2(pAthlete pt){
    Ptcellule2 tmp;
    tmp=malloc(sizeof(Cellule2));
    strcpy(tmp->cle,pt->lastName);
    tmp->pat=pt;
    return tmp;
}

void afficherEpreuve(pAthlete p){
    printf("%d ",p->e1.score );
    printf("%d ",p->e2.score );
    printf("%d ",p->e2a.score );
    printf("%d ",p->e3.score );
    printf("%d ",p->e4.score );
    printf("%d ",p->e5.score );
    printf("\n");
}

//fonction pour imprimer les informations pour un athlète
void imprime_athlete(pAthlete p){
    printf("%d ",p->AthId );
    printf("%d ",p->regId );
    printf("%d ",p->divId );
    printf("%s ",p->lastName );
    printf("%s ",p->firstName );
    printf("%s ",p->gender );
    printf("%d ",p->age );
    printf("%s ",p->height );
    printf("%s ",p->weight );
    afficherEpreuve(p);
    
}


//Il s'agit de la fonction de recherche d'un ID dans la table de hachage
/*La position dans l'arbre est déterminée à l'aide de la fonction "recherche" ci-dessus
 */
void rechercheID(Hashtable ht, char *val){
    int position;
    position=hash(val);//Détermination de la position dans la table de hachage
    Liste pt=ht[position];
    if (pt==NULL) {
        printf("ID %s NON TROUVE DANS NOS DONNEES!!!!\n",val);
        return;
    }
    while (pt!=NULL) {
        if(strcmp(pt->cle, val)==0){
            imprime_athlete(&pt->athlete);
        }
        pt=pt->suiv;
    }
    
}

//Fonction de recherche d'un nom dans la table de Hachage 2
void rechercheNom(Hashtable2 ht, char *val){
    int position;
    position=hash(val);
    Liste2 list =ht[position];
    if (list==NULL) {
        printf("LE NOM %s NON TROUVE DANS NOS DONNEES!!!!\n",val);
    }
    if (list!=NULL) {
        printf("Voici le-s athlète-s portant le nom %s :\n",val);
    }
    while (list!=NULL) {
        if(strcmp(list->cle, val)==0){
            imprime_athlete(list->pat);
        }
        list=list->suiv;
    }
}

//desallouer une cellule de la table de hachage1
void desallocation( Cellule **p){
    Cellule *tmp;
    while(*p!=NULL){
        tmp=*p;
        *p=tmp->suiv;
        free(tmp);
    }
   
}
//desalouer une cellule de la table de hachage2
void desallocation2( Cellule2 **p){
    Cellule2 *tmp;
    while(*p!=NULL){
        tmp=*p;
        *p=tmp->suiv;
        free(tmp);
    }
}

//pour desallouer toute la table de hachage1
void desalloc_thash(Hashtable ht){
    int i=0;
    while(i<TAILLE_TABLE_HASH)
    {
        while(ht[i]!=NULL){
            desallocation(&ht[i]);
        }
        i++;
    }
}
//fonction pour desallouer la table de hachage2
void desalloc_thash2(Hashtable2 ht){
    int i=0;
    while(i<TAILLE_TABLE_HASH)
    {
        while(ht[i]!=NULL){
            desallocation2(&ht[i]);
        }
        i++;
    }
}

int taille(Liste liste){
    int cpt=0;
    while (liste!=NULL) {
        cpt++;
        liste=liste->suiv;
    }
    return cpt;
    }
//fonction pour compter le nombre de collision dans la table
//si les collisions sont importante on modifie la fonction de hachage pour optimiser le programme
void collisions(Hashtable ht){
    for (int i=0; i<TAILLE_TABLE_HASH; i++) {
        printf("%d\n",taille(ht[i]));
    }
}
