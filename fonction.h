#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#define MAX 100
/*****************************************************************/
typedef struct Entete_TOF_index
{
    int nbBloc; // Nombre de blocs dans le fichier
    int nbEnreg; // Nombre d'enregistrements dans le fichier
} Entete_TOF_index;

/*typedef struct TOFF
{
    FILE *fichier;
    Entete_TOF_index entete;
} TOFF;
*/
/*********************DECLARATION DES STRUCTURES*****************************/
/*********structure d'enreg***********/
typedef struct TEnreg
{   int matricule;//la clé
    int efface;//le champs effacé
    char nom[30] ;//type chaine de caractere
    char prenom[30] ;
    short date_de_nais[3] ; // tableau de 8 entiers.
    unsigned char wilaya_nais;// entier 1
    unsigned char groupe_sang; // entier 2
    unsigned char grade ; // entier 3
    char force_arme; // entier 4
    char region_melit; // entier 5 ,sur 2 octets

}TEnreg;//la declaration de l'article

typedef TEnreg tab [MAX];  // max = nb de enregs dans un bloc , dans ce cas max=100 . taille de bloc = 8408 octets.

/**************structure De bloc*******************/
typedef struct TBloc
{tab t;//tableau d'enregistrement
int NbEnreg ;//le nombre d'enregistrement ds le tableau
int suiv  ;//le n° de prochain bloc
}TBloc;//declaration de bloc

/***************Structure de l'index***************/

typedef struct TEnrindex
{   int matricule; //la clé
    int num_bloc ;
    int pos_bloc ;
    int efface;//le champs effacé
}TEnrindex;//la declaration de l'article

typedef struct TableIndex {
   TEnrindex Table[300000];
   int Nb;
} TableIndex ;

typedef TEnrindex tabi[10000];

/**************structure De bloc*******************/
typedef struct TBlocIndex
{tabi t;//tableau d'enregistrement
int NbEnreg ;//le nombre d'enregistrement ds le tableau
}TBlocIndex;

/**************structure d'en_tete***************/
typedef struct
{   int num_Btete;//le n° de bloc tete
    int nb_enreg;//le nombre d'enregistrementd ds le fichier
    int nb_bloc;//le nombre de bloc ds le fichier
}TEn_Tete;//declaration du bloc en_tete
///********enetet index*************///


/************structure de fichierLNOF**************/
typedef struct
{   FILE *f;//declarer le fichier
    TEn_Tete *en_tete;
}LNOF;

/************structure de fichier TOF**************/
typedef struct
{   FILE *f;//declarer le fichier
    Entete_TOF_index *en_tete;
}TOF;

typedef enum //pour faciliter le choix des couleurs
{
    BLACK,          /**< black color 0*/
    BLUE,           /**< blue color 1*/
    GREEN,          /**< green color 2*/
    CYAN,           /**< cyan color 3*/
    RED,            /**< red color 4*/
    MAGENTA,        /**< magenta color 5*/
    BROWN,          /**< brown color 6*/
    LIGHTGRAY,      /**< light gray color 7*/
    DARKGRAY,       /**< dark gray color 8*/
    LIGHTBLUE,      /**< light blue color 9*/
    LIGHTGREEN,     /**< light green color 10*/
    LIGHTCYAN,      /**< light cyan color 11*/
    LIGHTRED,       /**< light red color 12*/
    LIGHTMAGENTA,   /**< light magenta color 13*/
    YELLOW,         /**< yellow color 14*/
    WHITE           /**< white color 15*/
} COLORS;

/***************imlementation du modele************/
void ouvrir (LNOF *fichier,char nom_fich[30],const char mode);
void fermer (LNOF *fichier);
void ecrire_dire(LNOF *fichier,int i,TBloc *buf);
void lire_dire(LNOF *fichier,int i,TBloc *buf);
void af_entete(LNOF *fichier,int num_caract,int val);
int en_tete(LNOF *fichier,int num_caract );
void alloc_bloc(LNOF *fichier,char nom_fich[10],TBloc *buf);


/************** les fonctions du TP ***************/
int random_number_between_two_bornes(int bi , int bs) ;
void gen_matricule(TEnreg * enreg);
void gen_nom(TEnreg * enreg) ;
void gen_prenom(TEnreg * enreg);
void gen_reg_melit(TEnreg * enreg);
void gen_wilaya(TEnreg * enreg);
void gen_g_sang(TEnreg * enreg);
void gen_grade(TEnreg * enreg);
void gen_force_arme(TEnreg * enreg);
//void creation_du_fichier ( LNOF* fichier , char nom_fichier[], int nb_enregs,TableIndex* Tableau);
//void chargement_initial( LNOF * mon_fich , char nom_fich[],int nbenreg, TableIndex * Tableau);







#endif // FUNCTION_H_INCLUDED
