#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hachage.h"
#include "tree.h"

// Conditionals
const bool          IS_DEBUG            = true;

// Constants
const unsigned int  BUFFER_SIZE         = 2048;
const unsigned int  FIELD_SIZE          = 20;
const char          CSV_DELIMITERS[]    = ",";

// Globals
char**              CSV_HEADER_FIELDS;
unsigned int        CSV_NB_FIELDS;

void display_header()
{
    for(unsigned int i = 0; i < CSV_NB_FIELDS; i++)
    {
        printf("%d - %s\n", i, CSV_HEADER_FIELDS[i]);
    }
}

void read_csv_header(char * header_line)
{
    //int     line_length = strlen(header_line);
    int     nb_fields   = 0;
    char*   string_ptr  = header_line;
    
    // Count the occurrences of delimiters
    while (NULL != string_ptr)
    {
        nb_fields++;
        string_ptr = strpbrk(string_ptr, CSV_DELIMITERS);
        if (NULL != string_ptr)
        {
            string_ptr++;
        }
    }
    
    // Globals allocation
    CSV_NB_FIELDS       = nb_fields;
    CSV_HEADER_FIELDS   = malloc( nb_fields * sizeof(char*) );
    
    char* token         = strtok(header_line, CSV_DELIMITERS);                  // strtok init.
    
    // Re-read the line to get the header of the columns
    for (/*unsigned*/ int i = 0; i < nb_fields; i++)
    {
        CSV_HEADER_FIELDS[i] = malloc( FIELD_SIZE * sizeof(char) );             // alloc
        memset(CSV_HEADER_FIELDS[i], 0, FIELD_SIZE);                            // 0 init.
        strcpy(CSV_HEADER_FIELDS[i], token);                                    // copy field in the structure
        token = strtok(NULL, CSV_DELIMITERS);                                   // loop to get a new field label
    }
    
    if (IS_DEBUG) display_header();
}

char *strtok_new(char * string, char const * delimiter){
    static char *source=NULL;
    char *p,*ret = 0;
    if(string!=NULL) source=string;
    if(source==NULL) return NULL;
    
    if((p=strpbrk(source,delimiter))!=NULL){
        *p=0;
        ret=source;
        source=++p;
    }
    return ret;
}

void read_csv_file(const char * filename,Hashtable tHash,Hashtable2 tHash2)
{
    FILE*   fp = fopen(filename, "r");
    char    buffer[BUFFER_SIZE];
    Tab t;
    init_donnee(&t);
    
    
    Ptcellule C;
    Ptcellule2 C2;
    
    pAthlete A;
    
    // Check if the file is really opened
    if (NULL == fp)
    {
        fprintf(stderr, "Unable to open file: %s\n", filename);
        return;
    }
    
    // 1st row is a header with field descriptions
    fgets(buffer, BUFFER_SIZE, fp);
    //read_csv_header(buffer);
    
    // Remaining rows are the entries
    while ( NULL != fgets(buffer, BUFFER_SIZE, fp) )
    {
        char*           token;
        unsigned int    i = 0;
        
        // strtok init.
        token = strtok_new(buffer, CSV_DELIMITERS);
        
        while (NULL != token)
        {
            if (IS_DEBUG)// printf("Field %d is %s\n", i++, token);
                
                strcpy(t[i++],token);
            
            token = strtok_new(NULL, CSV_DELIMITERS);
        }
        C=remplirCellule(t);//on recupère l'adresse d'une cellule qui a comme clé l'ID d'un athelète, les information de l'athlete  
        A=&(C->athlete);//on recupère juste l'adresse ou sont stocké juste les informations d'un seul athlète.
        C2=remplirCellule2(A);//on passe un pointeur d'athlete à ma fonction pour rempir la cellule2(cellule2 qui a comme cle:le nom, valeur: pointeur d'athlete) 
        ajout_table(C,tHash);//on rempli la  1ère table de hachage qui a comme clé :l'ID de l'athlète
        ajout_table2(C2, tHash2);//je rempli la 2ème table de hachage qui a comme clé: le nom de l'athlète
    }
   
    fclose(fp);
}

void usage(const char * prog_name)
{
    printf("Usage is %s your_csv_file\n\n", prog_name);
}

int main()
{
    Hashtable2 tHash2;
    Hashtable tHash;
    init_ht(tHash);//Initialisation de la table de Hachage 1
    init_ht2(tHash2);//Initialisation de la table de Hachage 2
    Tree t1;
    t1=NULL;

   
    read_csv_file("final_ranking.csv",tHash,tHash2);
    add_score(&t1,tHash);//construction de l'arbre selon le score 
    //add_rang(&t2,tHash);//construction de l'arbre selon le rang
    int i,j;
    i=1;
    j=1;
    for(unsigned int i = 0; i < CSV_NB_FIELDS; i++)
    {
        free(CSV_HEADER_FIELDS[i]);
    }
    free(CSV_HEADER_FIELDS);
    int choix1,param2;
    char choix[10];
    char param [100];
    char gender[5];
    //collisions(tHash);
    do
    {
        
        printf("=============================================================================\n");
        printf("|                                 MENU                                      |\n");
        printf("=============================================================================\n");
        printf("\n");
        printf("Choisissez une option parmi les chois suivants :\n");
        printf("1. Pour afficher le top 50\n");
        printf("2. Pour afficher le top 50 hommes ou femmes\n");
        printf("5. Pour rechercher un athlète via son identifiant\n");
        printf("6. Pour recherhcer un athlète via son nom de famille\n");
        printf("7. Pour afficher le classement d'une salle de CrossFit via son identifiant\n");
        printf("8. Pour afficher le classment des adhérents des salles de la métropole lilloise\n");
        printf("9. QUITTER\n");
        
        scanf("%s",choix);
        
        choix1=atoi(choix);
        if (choix1>48 || choix1<48+9) { //Ceci 48 correspond à l'Ascii de 1 et 57 celle de 9
            //On ne pourra don entrer dans ce if que si l'utilisateur a tapé un nombre entre 1 et 9
            switch (choix1){
                case 1:
                    printf("Voici le top 50 :\n");
                    i=1;
                    j=1;
                    print_lvr (t1,&i,&j);
                    break;
                    
                case 2:
                    printf("Veuillez choisir M(masculin) ou F(féminin)\n");
                    scanf("%s",gender);
                    i=1;
                    j=1;
                    print_lvr_gender(t1, &i, &j, gender);
                    break;
                case 5:
                    printf("Veuillez rentrer l'identifiant de la personne que vous recherchez\n");
                    scanf("%s",param);
                    rechercheID(tHash, param);
                    break;
                case 6:
                    printf("Veuillez rentrer le nom de la personne que vous recehrchez\n");
                    scanf("%s",param);
                    rechercheNom(tHash2, param);
                    break;
                case 7:
                    j=1;
                    printf("Veuillez rentrer l'identifiant de la salle\n");
                    scanf("%d",&param2);
                    print_lvr_salle(t1, &j, param2);
                    break;
                case 8:
                    
                    j=1;
                    printf("Voici le classement des salles de la métropole lilloise\n");
                    print_lvr_lille(t1, &j);
                    
                    break;
                    
            }
        }
    }while (choix1!=9); //tant que l'utilisateur n'aura pas tapé 9 on va rester dans la boucle
   
       
    
    clearTree(&t1);//desallouer l'arbre1 
    
    desalloc_thash( tHash);//desallouer la table de hachage 1
    desalloc_thash2(tHash2);//desallouer la table de hachage 2
    
    return 0;
}
