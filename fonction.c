#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include<string.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>



/***********************IMPLEMENTATION DU MODELE DU FICHIER***************************************/

/************OUVERTURE***************/
void ouvrir (LNOF *fichier,char nom_fich[],const char mode)//ouvrir un fichier de type LNOF en mode voulu
{

    fichier->en_tete = malloc(sizeof(TEn_Tete)) ;

if ((mode=='n')||(mode=='N'))//si le mode est nouveau ie:le fichier n'existe pas déjà alors
    {
         fichier->f=fopen(nom_fich,"wb+");//ouvrir un fichier en mode ecriture binaire
         fichier->en_tete->num_Btete= 1;//initialiser les champs 1 ET 3 de l'en_tete à -1
         fichier->en_tete->nb_enreg=0;//initialiser le nombre d'enregistrements à 0
         fichier->en_tete->nb_bloc=0;
         fwrite(fichier->en_tete,sizeof(TEn_Tete),1,fichier->f);//ecrire l'en_tete ds le fichier binaire

    }
    else
    {
        if ((mode=='a')||(mode=='A'))//si le mode est ancien ie:le fichier existe
        {
          fichier->f=fopen(nom_fich,"rb+");//ouvrir le fichier en mode lecture binaire
          if (fichier->f==NULL) printf("\n\t\t<<Le fichier n'existe pas...>>");//si erreur d'ouverture
          else//sinon
         {fread(fichier->en_tete,sizeof(TEn_Tete),1,fichier->f);}//recuperer le contenu de l'entete ds la variable en_tete

        }
       // else printf("le mode errone.");
    }
}

/************FERMETURE*********************/
void fermer (LNOF *fichier)//fermer un fichier
{   rewind(fichier->f);//on se positionne au debut de fichier
    fwrite(fichier->en_tete,sizeof(TEn_Tete),1,fichier->f);//on enregistre les modifications effectuées sur l'en_tete
    fclose(fichier->f);//on ferme le fichier
    free(fichier->en_tete);//liberer la zone en_tete reservée
}
/************ ECRITURE DIRECTE*************/
void ecrire_dire(LNOF *fichier,int i,TBloc *buf)//ecriture directe du contenu de buf ds le fichier à la position i
{   rewind(fichier->f);
    fseek(fichier->f,sizeof(TEn_Tete)+(i-1)*sizeof(TBloc),SEEK_SET);//se positionner à la place exacte
    fwrite(buf,sizeof(TBloc),1,fichier->f);//ecriture
}


/****************LECTURE DIRECTE*************/
void lire_dire(LNOF *fichier,int i,TBloc *buf)//lecture directe du contenu de fichier à la position i ds le buf
{   rewind(fichier->f);
    fseek(fichier->f,sizeof(TEn_Tete)+(i-1)*sizeof(TBloc),SEEK_SET);//se positionner à la place exacte
    fread(buf,sizeof(TBloc),1,fichier->f);//lecture
}

/****************AFF_ENTETE*******************/
void af_entete(LNOF *fichier,int num_caract,int val)//affecter à la caracteristique num_caract la val
{
  switch(num_caract)
  {
      case 1:fichier->en_tete->num_Btete = val;
     rewind(fichier->f);//on se positionne au debut de fichier
      fwrite(fichier->en_tete,sizeof(TEn_Tete),1,fichier->f);
     break;
      case 2:fichier->en_tete->nb_enreg=val;
      rewind(fichier->f);//on se positionne au debut de fichier
      fwrite(fichier->en_tete,sizeof(TEn_Tete),1,fichier->f);
     break;
      case 3:fichier->en_tete->nb_bloc=val;
      rewind(fichier->f);//on se positionne au debut de fichier
      fwrite(fichier->en_tete,sizeof(TEn_Tete),1,fichier->f);
     break;
      default: printf("\n\t\t<<Le numero errone>>");
  }
}


/*******************EN_TETE*********************/
int en_tete(LNOF *fichier,int num_caract )//retourner la cracterstique num_caract ds val
{int val;
    switch(num_caract)
  {
      case 1:val=fichier->en_tete->num_Btete; break;
      case 2:val=fichier->en_tete->nb_enreg; break;
      case 3:val=fichier->en_tete->nb_bloc; break;
      default: printf("\n\t\t<<Le numero errone>>");
  }
  return val;
}


///************ Initialisation du bloc***************/
void init_bloc(TBloc *buf)//initialise un buffer
{int i;
 (*buf).NbEnreg=0;//initialiser le nb d'articles à 0
 for(i=0;i<MAX;i++)
 {
     (*buf).t[i].efface=1;//initialiser tout les champs efface de tableau à vrai
 }
 }

/*******************alloc_bloc***********************/
void alloc_bloc(LNOF *fichier,char nom_fich[30],TBloc *buf)//initialise un buffer
{int i;
 (*buf).suiv=-1;//initialiser le champs suiv à nil
 (*buf).NbEnreg=0;//initialiser le nb d'articles à 0
 for(i=0;i<MAX;i++)
 {
     (*buf).t[i].efface=1;//initialiser tout les champs efface de tableau à vrai
 }
 }



/***********************IMPLEMENTATION DU MODELE DE L'INDEX***************************************/

/************OUVERTURE******************************/
void ouvrir_index(TOF *fichier,char nom_fich[],const char mode){

    fichier->en_tete= malloc(sizeof(Entete_TOF_index)) ;

if ((mode=='n')||(mode=='N'))//si le mode est nouveau ie:le fichier n'existe pas déjà alors
    {
         fichier->f=fopen(nom_fich,"wb+");//ouvrir un fichier en mode ecriture binaire

         fichier->en_tete->nbEnreg=0;//initialiser le nombre d'enregistrements à 0
         fichier->en_tete->nbBloc=0;
         fwrite(fichier->en_tete,sizeof(Entete_TOF_index),1,fichier->f);//ecrire l'en_tete ds le fichier binaire

    }
    else
    {
        if ((mode=='a')||(mode=='A'))//si le mode est ancien ie:le fichier existe
        {
          fichier->f=fopen(nom_fich,"rb+");//ouvrir le fichier en mode lecture binaire
          if (fichier->f==NULL) printf("\n\t\t<<Le fichier n'existe pas...>>");//si erreur d'ouverture
          else//sinon
         {fread(fichier->en_tete,sizeof(Entete_TOF_index),1,fichier->f);}//recuperer le contenu de l'entete ds la variable en_tete

        }
       // else printf("le mode errone.");
    }
}

/************FERMETURE***************/
void fermer_index(TOF * fichier){
    rewind(fichier->f);//on se positionne au debut de fichier
    fwrite(fichier->en_tete,sizeof(Entete_TOF_index),1,fichier->f);//on enregistre les modifications effectuées sur l'en_tete
    fclose(fichier->f);//on ferme le fichier
    free(fichier->en_tete);//liberer la zone en_tete reservée
}

/****************LECTURE DIRECTE**************/
void lire_dire_index(TOF * F,int i,TBlocIndex *buf){
rewind(F->f);
fseek(F->f,sizeof(Entete_TOF_index)+(i-1)*sizeof(TBlocIndex),SEEK_SET);
fread(buf,sizeof(TBlocIndex),1,F->f);
}
 /****************ECRITURE DIRECTE*************/
void ecrire_dire_index(TOF * Fich,int i,TBlocIndex *buf){
rewind(Fich->f);
fseek(Fich->f,sizeof(Entete_TOF_index)+(i-1)*sizeof(TBlocIndex),SEEK_SET);
  //printf(" the size of a block of index is %d bytes\t", sizeof(TBlocIndex));
fwrite(buf,sizeof(TBlocIndex),1, Fich->f);
//printf("we did a fwrite");
}

/*******************EN_TETE INDEX**************/
int en_tete_index(TOF *fichier,int num_caract )//retourner la cracterstique num_caract ds val
{int val;
    switch(num_caract)
  {

      case 1:val=fichier->en_tete->nbEnreg; break;
      case 2:val=fichier->en_tete->nbBloc; break;
      default: printf("\n\t\t<<Le numero errone>>");
  }
  return val;
}

/****************AFF_ENTETE*******************/

void af_entete_index(TOF *fichier,int num_caract,int val)//affecter à la caracteristique num_caract la val
{
  switch(num_caract)
  {
     // case 1:fichier->en_tete->num_Btete=val;
     //  rewind(fichier->f);//on se positionne au debut de fichier
      //fwrite(fichier->en_tete,sizeof(Entete_TOF_index),1,fichier->f);
  //  break;
      case 1:fichier->en_tete->nbEnreg=val;
      //rewind(fichier->f);//on se positionne au debut de fichier
    //fwrite(fichier->en_tete,sizeof(Entete_TOF_index),1,fichier->f);
     break;
      case 2:fichier->en_tete->nbBloc=val;
      //rewind(fichier->f);//on se positionne au debut de fichier
    //fwrite(fichier->en_tete,sizeof(Entete_TOF_index),1,fichier->f);
     break;
      default: printf("\n\t\t<<Le numero errone>>");
  }
}

///************ Initialisation du bloc***************/
void init_bloc_index(TBlocIndex *buf)//initialise un buffer
{int i;
 (*buf).NbEnreg= 0;//initialiser le nb d'articles à 0
 for(i=0;i<10000;i++)
 {
     (*buf).t[i].efface = 1;//initialiser tout les champs efface de tableau à vrai
 }
 }




/***********************************************/
/********** les fonctions du TP ****************/

int random_number_between_two_bornes(int bi , int bs){
int num = (rand()% (bs - bi +1 ))  + bi;
           return num ;
}
///********generer un matricule **********/
void gen_matricule(TEnreg * enreg){
 enreg->matricule =  ((rand()%9 )+1)+((rand()%9 )+1)*10+((rand()%9 )+1)*100+((rand()%9 )+1)*1000+((rand()%9 )+1)*10000+((rand()%9 )+1)+((rand()%9 )+1)*100000;
}

///********generer un nom *************/
void gen_nom(TEnreg * enreg){
 int length ; // longueur du nom
 int nom_en_chifres[30]; // var temp pour les chiffres aleatoires generes
 length = random_number_between_two_bornes(4,30);
 for ( int i =0;i< length;i++){
    nom_en_chifres[i] = random_number_between_two_bornes(1,26);
    }  // fin boucle for .
     for (int i=0 ; i< length ; i++){
        enreg->nom[i]= (nom_en_chifres[i] + 96);
        } // fin boucle for .
            enreg->nom[length] = '\0';
} // fin du procedure
///**************generer un prenom *****************/

void gen_prenom(TEnreg * enreg){
 int length ; // longueur du nom
 int nom_en_chifres[30]; // var temp pour les chiffres aleatoires generes
 length = random_number_between_two_bornes(4,30);
 for ( int i =0;i< length;i++){
    nom_en_chifres[i] = random_number_between_two_bornes(1,26);
    }  // fin boucle for.

     for (int i=0 ; i< length ; i++){
        enreg->prenom[i]= (nom_en_chifres[i] + 96);
        } // fin boucle for .
         enreg->prenom[length] = '\0';

}
///**************generer une date *****************/
void gen_date(TEnreg * enreg){
enreg->date_de_nais[1] = random_number_between_two_bornes(1,12);
     enreg->date_de_nais[0]=random_number_between_two_bornes(1945,2002);
     if(enreg->date_de_nais[1]== 2 && enreg->date_de_nais[0]%4 == 0){
            enreg->date_de_nais[2] = random_number_between_two_bornes(1,28);
        }else if(enreg->date_de_nais[1]== 2 && enreg->date_de_nais[0]%4 != 0) {
            enreg->date_de_nais[2] = random_number_between_two_bornes(1,29);
            } else if(enreg->date_de_nais[1]==4 || enreg->date_de_nais[1]==6 ||enreg->date_de_nais[1]==9 || enreg->date_de_nais[1]==11){
                enreg->date_de_nais[2] = random_number_between_two_bornes(1,30);
            }else{
            enreg->date_de_nais[2] = random_number_between_two_bornes(1,31);
            }

}

///*************generer le groupe sanguin ************//
void gen_g_sang(TEnreg * enreg){
 int y ;
 y = random_number_between_two_bornes(1,8);
 enreg->groupe_sang = y ;
}

///************* generer la wilaya **********/
void gen_wilaya(TEnreg * enreg){
 int y ;
 y = random_number_between_two_bornes(1,58);
 enreg->wilaya_nais = y ;
}
///************* generer le grade *********/
void gen_grade(TEnreg * enreg){
int y = random_number_between_two_bornes(1,17);
enreg->grade = y ;
}
///************ generer la force arme **********/
void gen_force_arme(TEnreg * enreg){
 int y = random_number_between_two_bornes(1,8);
 enreg->force_arme = y ;

}
///************generer la region melitaire*******/
void gen_reg_melit(TEnreg * enreg){
 int y = random_number_between_two_bornes(1,6);
 enreg->region_melit = y ;

}

///****************************************************************************************
///******************MODULES DE MANIPULATION DU FICHIER PRINCIPAL**********************///
///****************************************************************************************

///****** Module du chargement initial du fichier principal ******/
void chargement_initial( LNOF * mon_fich , char nom_fich[],int nbenreg, TableIndex * Tableau ,int * nblire, int * nbecrire){
    TBloc buffer ;
    int j = 0 , ind = 0 ;
    int i = 1 , b=1 ;
    buffer.suiv = 1 ;
    init_bloc(&buffer);
    int special ;
    Tableau->Nb =0;
    if ( nbenreg%100 == 0){
      special = 1 ;
    } else{
      special =0;
        }
   while(i <= nbenreg){
      gen_date(&(buffer.t[j]));
      buffer.t[j].efface = 0 ;
      gen_nom( &(buffer.t[j]));
      gen_force_arme(&(buffer.t[j]));
      gen_grade(&(buffer.t[j]));
      gen_g_sang(&(buffer.t[j]));

      gen_matricule(&(buffer.t[j])) ;
      gen_prenom(&(buffer.t[j]));
      gen_reg_melit(&(buffer.t[j]));
      gen_wilaya(&(buffer.t[j]));
      buffer.NbEnreg++;
      //table index est une struct of 30*1000 enregs and NB .
      Tableau->Table[i-1].matricule = buffer.t[j].matricule;// tableau est un ptr vers table index. TAB ausssi
      Tableau->Table[i-1].num_bloc = b;
      Tableau->Table[i-1].pos_bloc = j;
      Tableau->Table[i-1].efface = buffer.t[j].efface ;
      Tableau->Nb++;
        if( buffer.NbEnreg == MAX){
            buffer.suiv++;
            ecrire_dire(mon_fich , b , &buffer);
            (*nbecrire)++;
            init_bloc(&buffer);

            buffer.suiv++;
            b++;
            j=0 ;
            i++;
            ind++;
        } else {
        j++;
        i++;
        ind++;
        }// fin else
       } // fin while

   if ( special == 1 ){
   lire_dire(mon_fich , b-1 , &buffer) ;
   //printf(" le liredire de b-1 : buffer.nbenre=%d \n",buffer.NbEnreg);
   buffer.suiv = -1 ;
   ecrire_dire(mon_fich , b-1 , &buffer) ;
   (*nbecrire)++;
   af_entete(mon_fich,2,(i-1));
   //printf(" the value of b=%d , da5el l if special  \n",b);
    }
      else {
    if ( buffer.NbEnreg < MAX){
    buffer.suiv = -1 ;
    ecrire_dire(mon_fich , b ,&buffer);
    (*nbecrire)++;
     af_entete(mon_fich,2,(i-1));
        }
   }
   quicksort(Tableau->Table,0,nbenreg-1);

   int suprime = Epuration(mon_fich,nom_fich,Tableau->Table,nbenreg,nblire,nbecrire);
   int kk = i-1- suprime ;

    af_entete(mon_fich,2,kk);
    if (special){
        af_entete(mon_fich,3 ,b-1);
    }
    else{
        af_entete(mon_fich,3 ,b);
    }

  TOF fixx ;
  TOF * index = &fixx ;
  creation_du_fichier_index(index,"Fichier_Index_officiel.bin",Tableau,nblire,nbecrire);
  // ici l'index est ferme normalement .
  ouvrir_index(index,"Fichier_Index_officiel.bin",'a');
  af_entete_index(index,1 , en_tete_index(index,1) - suprime);
  fermer_index(index);
  //ici index est ferme nomralement .

}
 // fin chargement initial

///************ module de creation du FICHIER*****************/
void creation_du_fichier ( LNOF* fichier , char nom_fichier[], int nb_enregs, TableIndex * Tableau , int * nblire, int * nbecrire){
  ouvrir(fichier,nom_fichier,'n');
  fermer(fichier);
  ouvrir(fichier,nom_fichier,'a');
  chargement_initial (fichier,nom_fichier,nb_enregs,Tableau,nblire,nbecrire);
  fermer(fichier);
}

/******************Epuration***************/
int Epuration(LNOF *fichier,char nom_fich[],TEnrindex tindex[],int n,int * nblire, int * nbecrire){
    int cpt=0;
    TBloc Buffer;
    ouvrir(fichier,nom_fich,'a');
    for(int i=0;i<=n ;i++){
        if (tindex[i].matricule==tindex[i+1].matricule){
                tindex[i+1].efface = 1;
                cpt++;
                lire_dire(fichier,tindex[i+1].num_bloc,&Buffer);
                (*nblire)++;
                Buffer.NbEnreg--;
                Buffer.t[tindex[i+1].pos_bloc].efface = 1;
                ecrire_dire(fichier,tindex[i+1].num_bloc,&Buffer);
                (*nbecrire)++;
                }
    }
return cpt ;}


///************Quick sort **********/
void quicksort(TEnrindex number[],int first,int last){
   int i, j, pivot, temp1,temp2,temp3,temp4;
   if(first<last){
      pivot=first;
      i=first;
      j=last;
      while(i<j){
         while(number[i].matricule<=number[pivot].matricule&&i<last)
            i++;
         while(number[j].matricule>number[pivot].matricule)
            j--;
         if(i<j){
            temp1=number[i].matricule;
            temp2=number[i].num_bloc ;
            temp3=number[i].pos_bloc ;
            temp4=number[i].efface   ;
            number[i].matricule=number[j].matricule;
            number[i].num_bloc =number[j].num_bloc ;
            number[i].pos_bloc =number[j].pos_bloc ;
            number[i].efface   =number[j].efface   ;
            number[j].matricule=temp1;
            number[j].num_bloc =temp2;
            number[j].pos_bloc =temp3;
            number[j].efface   =temp4;
         }
      }
      temp1=number[pivot].matricule;
      temp2=number[pivot].num_bloc ;
      temp3=number[pivot].pos_bloc ;
      temp4=number[pivot].efface   ;
      number[pivot].matricule=number[j].matricule;
      number[pivot].num_bloc =number[j].num_bloc ;
      number[pivot].pos_bloc =number[j].pos_bloc ;
      number[pivot].efface   =number[j].efface   ;
      number[j].matricule=temp1;
      number[j].num_bloc =temp2;
      number[j].pos_bloc =temp3;
      number[j].efface   =temp4;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);

   }
 }

/******************Insertion dans le fichier principal *******************/
 void reglage(){//pour le controle de saisie
int caract = 0;
while ((caract!='\n') && (caract!= EOF))
    {caract=getchar();}
}

/********/
void insertion_LNOF(LNOF *fichier,char nom_fich[],TEnreg *n, int* blc , int* dep){//inserer un enregistrement ds un fichier
int i,j,pos_lib,num_bloc,affirm,k,reg=1;
TBloc buf;
ouvrir(fichier,nom_fich,'A');//ouvrir le fichier en mode ancien
num_bloc=en_tete(fichier,3);
lire_dire(fichier,num_bloc,&buf);
printf("\n num block=%d",num_bloc);

if ( buf.NbEnreg ==100 ){

    (*blc)= num_bloc+1 ;
    (*dep)= 0;
    buf.suiv=num_bloc+1;//faire le chainage avec le nouveau bloc
    ecrire_dire(fichier,num_bloc,&buf);//sauvegarder les modifications
    init_bloc(&buf);
    n->efface=0;
    buf.t[0] = (*n);
    buf.NbEnreg = 1 ;
    buf.suiv =-1 ;
    num_bloc++;
    ecrire_dire(fichier,num_bloc,&buf);
    af_entete(fichier,3,num_bloc);
    i=en_tete(fichier,2);//lire le nombre d'articles ds le fichier
    i++;
    af_entete(fichier,2,i);

    }else{
        int g=0;
        while( (buf.t[g].efface == 0)  && (g<100)){
            g++;
        }
        n->efface=0;
        (*blc)= num_bloc ;
        (*dep)= g;
        buf.t[g] = *n ;
        buf.NbEnreg++;
        i=en_tete(fichier,2);//lire le nombre d'articles ds le fichier
        i++;
        af_entete(fichier,2,i);//l'incrementer
        ecrire_dire(fichier,num_bloc,&buf);//ecrire le buffer
 }
fermer(fichier);//fermer le fichier
}

///************ modifier la region militaire*********/
void modif_reg_melit ( LNOF * fich_prin , TOF * fich_index , char nom_fich_pr[] , char nom_fich_inx[],int * nblire, int * nbecrire)
{  int trouve , i , j , bloc , depl;
  TBloc buff ;
  int matricule ;
ouvrir_index(fich_index,nom_fich_inx,'a');
  do{
    printf(" veuillez entrer un matricule svp \n") ;
    scanf("%d", &matricule);
    rechDicho_index(matricule,fich_index,&trouve ,&i,&j,nblire,nbecrire,&bloc,&depl);

  }while(trouve == 0);

int new_reg ;
    printf(" veuillez entrer la nouvelle region militaire \n");
    scanf("%d", &new_reg);
    ouvrir(fich_prin,nom_fich_pr,'a');
    //rechDicho_index(matricule,fich_index,&trouve ,&i,&j,&nblire,&nbecrire,&bloc,&depl);

    lire_dire(fich_prin,bloc,&buff);
    (*nblire)++;
    buff.t[depl].region_melit = new_reg;
    ecrire_dire(fich_prin,bloc,&buff);
    fermer(fich_prin);
    fermer_index(fich_index);
     printf(" modification avec succes \n");
}












///*************************suprimmer un enreg ******************///
void suprim_enreg(LNOF * fich_prin , TOF * fich_index , char nom_fich_pr[] , char nom_fich_inx[], int * nblire, int * nbecrire){
    int trouve , i , j , bloc , depl ;
    TBloc buff ;
    ouvrir_index(fich_index,nom_fich_inx,'a');
    TBlocIndex buff_ind ;
    int mat ;
    do{
    printf("\n Veuillez introduire le matricule à supprime SVP \n");
    scanf("%d",&mat);
    rechDicho_index(mat,fich_index,&trouve ,&i,&j,nblire,nbecrire,&bloc,&depl);}
    while(trouve == 0);

    ouvrir(fich_prin,nom_fich_pr,'a');
    lire_dire(fich_prin,bloc,&buff);
    (*nblire)++;;
    buff.t[depl].efface = 1 ;
    buff.NbEnreg--;
    ecrire_dire(fich_prin,bloc,&buff);
    (*nbecrire)++;
    af_entete(fich_prin,2, en_tete(fich_prin,2) - 1 );
    lire_dire_index(fich_index,i,&buff_ind);
    (*nblire)++;
    buff_ind.t[j].efface = 1 ;
    buff_ind.NbEnreg--;
    ecrire_dire_index(fich_index,i,&buff_ind);
    (*nbecrire)++;
    af_entete_index(fich_index,2, en_tete_index(fich_index,2) - 1 );
    fermer(fich_prin);
    fermer_index(fich_index);
}


///****Suppression d'un seul enregistrement selon la force armee**********///
void sup_selon_force(LNOF *fichier,char nom_fich[],TOF * fich_index , char nom_fich_index[],int * nblire, int * nbecrire){
 int trouve , depl ,bloc ;
 int blk,depx ;
    TBloc Buffer;
    TBlocIndex buff_index ;
    int mat;
    int force ;
    int i=1,j=0;

    printf(" \n donnez la force a effacer svp \n");
    scanf("%d",&force);
    ouvrir_index(fich_index,nom_fich_index,'a');
    ouvrir(fichier,nom_fich,'a');

    while (i<=en_tete(fichier,3)){

        lire_dire(fichier,i,&Buffer);
        (*nblire)++;
        while (j < 100){
        if(force == Buffer.t[j].force_arme ){
                mat = Buffer.t[j].matricule ;
                rechDicho_index(mat,fich_index,&trouve ,&blk,&depx,nblire,nbecrire,&bloc,&depl);
                lire_dire_index(fich_index,blk,&buff_index);
                (*nblire)++;
                buff_index.t[depx].efface = 1 ;
                buff_index.NbEnreg--;
                ecrire_dire_index(fich_index,blk,&buff_index);
                (*nbecrire)++;

                Buffer.t[j].efface = 1 ;
                Buffer.NbEnreg--;
        }
        j++;
        }
        ecrire_dire(fichier,i,&Buffer);
        (*nbecrire)++;
        i++;
        j=0;
        }
fermer(fichier);
fermer_index(fich_index);
}


///****************Fragmentation du fichier***************///
void Fragmentation(LNOF *fichier,char nom_fich[],LNOF*fichier1,LNOF*fichier2,LNOF*fichier3,LNOF*fichier4,LNOF*fichier5,LNOF*fichier6){
TBloc buffer,buffer1,buffer2,buffer3,buffer4,buffer5,buffer6;

ouvrir(fichier,nom_fich,'a');
ouvrir(fichier1,"Frag1",'n');
fermer(fichier1);
ouvrir(fichier1,"Frag1",'a');
ouvrir(fichier2,"Frag2",'n');
fermer(fichier2);
ouvrir(fichier2,"Frag2",'a');
ouvrir(fichier3,"Frag3",'n');
fermer(fichier3);
ouvrir(fichier3,"Frag3",'a');
ouvrir(fichier4,"Frag4",'n');
fermer(fichier4);
ouvrir(fichier4,"Frag4",'a');
ouvrir(fichier5,"Frag5",'n');
fermer(fichier5);
ouvrir(fichier5,"Frag5",'a');
ouvrir(fichier6,"Frag6",'n');
fermer(fichier6);
ouvrir(fichier6,"Frag6",'a');
int i=1,i1=1,i2=1,i3=1,i4=1,i5=1,i6=1;
int j=0,j1=0,j2=0,j3=0,j4=0,j5=0,j6=0;

init_bloc(&buffer1);
init_bloc(&buffer2);
init_bloc(&buffer3);
init_bloc(&buffer4);
init_bloc(&buffer5);
init_bloc(&buffer6);


while (i<en_tete(fichier,3)){
    lire_dire(fichier,i,&buffer);
    for (j=0;j<100;j++){
        if (buffer.t[j].region_melit ==1){
                buffer1.t[j]=buffer.t[j];
                j1++;
                if (j1 == MAX){
                    buffer1.NbEnreg = MAX;
                    ecrire_dire(fichier1,i1,&buffer1);
                    i1++;
                    init_bloc(&buffer1);
                    j1=0;
                }
        }else if (buffer.t[j].region_melit == 2){
                buffer2.t[j]=buffer.t[j];
                j2++;
                if (j2 == MAX){
                    buffer2.NbEnreg = MAX;
                    ecrire_dire(fichier2,i2,&buffer2);
                    init_bloc(&buffer2);
                    i2++;
                    j2=0;
                }
              }else if (buffer.t[j].region_melit == 3){
                  buffer3.t[j]=buffer.t[j];
                  j3++;
                  if (j3 == MAX){
                      buffer3.NbEnreg = MAX;
                      ecrire_dire(fichier3,i3,&buffer3);
                      init_bloc(&buffer3);
                      i3++;
                      j3=0;
                  }
                  }else if (buffer.t[j].region_melit == 4){
                        buffer4.t[j]=buffer.t[j];
                        j4++;
                        if (j4 == MAX){
                            buffer4.NbEnreg = MAX;
                            ecrire_dire(fichier4,i4,&buffer4);
                            init_bloc(&buffer4);
                            i4++;
                            j4=0;
                        }
                        }else if (buffer.t[j].region_melit == 5){
                                buffer5.t[j]=buffer.t[j];
                                j5++;
                                if (j5 == MAX){
                                    buffer5.NbEnreg = MAX;
                                    ecrire_dire(fichier5,i5,&buffer5);
                                    init_bloc(&buffer5);
                                    i5++;
                                    j5=0;
                                    }
                                }else if (buffer.t[j].region_melit == 6){
                                    buffer6.t[j]=buffer.t[j];
                                    j6++;
                                    if (j6 == MAX){
                                        buffer6.NbEnreg = MAX;
                                        ecrire_dire(fichier6,i6,&buffer6);
                                        init_bloc(&buffer6);
                                        i6++;
                                        j6=0;
                                    }
                                }

    }
    i++;
}
buffer1.NbEnreg = j1-1; ecrire_dire(fichier1,i1,&buffer1);
buffer2.NbEnreg = j2-1; ecrire_dire(fichier2,i2,&buffer2);
buffer3.NbEnreg = j3-1; ecrire_dire(fichier3,i3,&buffer3);
buffer4.NbEnreg = j4-1; ecrire_dire(fichier4,i4,&buffer4);
buffer5.NbEnreg = j5-1; ecrire_dire(fichier5,i5,&buffer5);
buffer6.NbEnreg = j6-1; ecrire_dire(fichier6,i6,&buffer6);

af_entete(fichier1,3,i1);
af_entete(fichier2,3,i2);
af_entete(fichier3,3,i3);
af_entete(fichier4,3,i4);
af_entete(fichier5,3,i5);
af_entete(fichier6,3,i6);
fermer(fichier1);fermer(fichier2);fermer(fichier3);fermer(fichier4);fermer(fichier5);fermer(fichier6);
printf("Fragmentation successfully done \n Vous trouverez vos six fichiers dans le dossier courant.");
}

///****************************************************************************************
///******************MODULES DE MANIPULATION DU FICHIER D'INDEX**********************///
///****************************************************************************************

 /**********Module du chargement initial DE L'INDEX******************/
void chargement_index(const char nom_fich[],TableIndex * Tableau , TOF* fichier_index,int *nblire , int * nbecrire){
    TBlocIndex buffer ;
    int j = 0 ;
    int i = 0 , b=1 ;
    init_bloc_index(&buffer);
    int special ;

    if ( (Tableau->Nb % 10000) == 0) {
        special=1;
    } else{
    special=0;}

      while(i < Tableau->Nb ){
      buffer.t[j].matricule = Tableau->Table[i].matricule;
      buffer.t[j].num_bloc = Tableau->Table[i].num_bloc ;
      buffer.t[j].pos_bloc = Tableau->Table[i].pos_bloc ;
      buffer.t[j].efface = Tableau->Table[i].efface;

      buffer.NbEnreg++;

           if( buffer.NbEnreg == 10000){
            ecrire_dire_index( fichier_index ,b, &buffer);
            (*nbecrire)++;
            init_bloc_index(&buffer);

            b++;
            j=0 ;
            i++;
        } else {
        j++;
        i++;
        }
       }

       if( special){
            af_entete_index(fichier_index,2,b-1);
            af_entete_index(fichier_index,1,i);
             i=0;
       } else{

       if ( buffer.NbEnreg < 10000){
            af_entete_index(fichier_index,2,b);
            af_entete_index(fichier_index,1,i);

            ecrire_dire_index(fichier_index, b ,&buffer);
            (*nbecrire)++;
        }
        }

  //fclose(f);
  //printf("\n nb enreg %d , nb bloc %d  \t \t\t\t\n", Tableau->Nb , b);
  //fclose(findex);
 }

/************creation du fichier index******************************/
void creation_du_fichier_index ( TOF* fichier , char nom_fichier[], TableIndex * Tableau ,int * nblire, int * nbecrire){
  ouvrir_index(fichier,nom_fichier,'n');
  fermer_index(fichier);
  ouvrir_index(fichier,nom_fichier,'a');
  chargement_index(nom_fichier,Tableau,fichier, nblire , nbecrire);
  fermer_index(fichier);
}

/******************recherche dichotomique ( pour le fichier index )**************/
void rechDicho_index(int matricule_cher , TOF * fichier, int* trouv,int* i,int* j,int *nb_lireDir, int *nb_ecrireDir , int * bloc, int* dep)
{
    *i = 0;
    *j = 0;
    TBlocIndex buf;
     *bloc = -1;
     *dep = -1 ;
     *trouv = 0;
    int stop = 0;
    int infB, supB; // les numéros des blocs sup et inf de la recherche externe
    int infE, supE; // les positions des enregistrements sup et inf de la recherche interne
    /* Traitement du cas ou le fichier est vide */
    if (en_tete_index(fichier,1) == 0)
    {

        *i = 1;
        *j = 0;
        return;
    }

       /* Recherche externe */
   infB = 1; // le premier bloc
    supB = en_tete_index(fichier, 2);
     //le dernier bloc
    while(infB<=supB && !(*trouv) && !stop)
    { //  printf("\n hello there , inside l while");
        *i = (infB + supB) / 2; // le numéro du bloc du milieu
        int nb = *i;
        lire_dire_index(fichier, nb, &buf);
        (*nb_lireDir)++;

        if (buf.t[0].matricule <= matricule_cher && matricule_cher <= buf.t[buf.NbEnreg-1].matricule)
        { /* Recherche interne */
            infE = 0; // le premier enregistrement du bloc
            supE = 9999;
            while(infE<=supE && !(*trouv))
            {
                *j = (infE + supE) / 2; // l'indice de l'enregistrement du milieu
                if (buf.t[*j].matricule ==  matricule_cher){
                    *trouv = 1;
                    *bloc = buf.t[*j].num_bloc;
                    *dep = buf.t[*j].pos_bloc; }
                else
                {
                    if (buf.t[*j].matricule > matricule_cher)
                        supE = *j - 1;
                    if (buf.t[*j].matricule < matricule_cher)
                        infE = *j + 1;
                }
            }
            if (infE>supE) // le numéro recherché n'existe pas dans le bloc
                *j = infE; // la position ou il faut l'inséerer alors
                stop = 1;
            /* Fin de la recherche interne */
        }
        else
        {
            if (buf.t[0].matricule > matricule_cher)
                supB = *i - 1;
            if (matricule_cher > buf.t[buf.NbEnreg-1].matricule)
                infB = *i + 1;
        }
    }

    if (infB>supB && matricule_cher<buf.t[0].matricule) // le numéro recherché est plus petit que
        *j = 0;                                 // tous les numéros qui existent dans le fichier

    if (infB>supB && matricule_cher>buf.t[buf.NbEnreg-1].matricule) // le numéro recherché est plus grand que
    {                                             // tous les numéros qui existent dans le fichier

        if (buf.NbEnreg == 10000) // le dernier bloc est plein
        {
            *i = infB; // il faut insérer l'enregistrement dans un nouveau bloc
            *j = 0;
        }
        else // le dernier bloc n'est pas encore plein
            *j = buf.NbEnreg; // il faut l'insérer dans le dernier bloc à la première position libre
    }
    /* Fin de la recherche externe */
  }

///***************insertion TOF pour l'index**************///
int insertion_TOF (TOF * f, TEnrindex enreg, int *nb_lireDir, int *nb_ecrireDir){
    int bloc , dep ;
    int trouv,i,j;

    // où doit être insérer l'enregistrement s'il n'existe pas encore le numéro dans le fichier
    rechDicho_index(enreg.matricule,f,&trouv,&i,&j,nb_lireDir,nb_ecrireDir ,&bloc,&dep);
    if (trouv) return 0;                // le numéro de CCP existe déja dans le fichier et on ne peut pas le réinsérer
    else{                               // le numéro de CCP n'existe pas dans le fichier, il faut l'insérer à l'emplacement (i,j)

        TBlocIndex buf;
        TEnrindex x;
        int k,continu=1;
        while ((continu==1) && (i<=en_tete_index(f,1)))
        {
            lire_dire_index(f,i,&buf);
            (*nb_lireDir)++;
            x = buf.t[buf.NbEnreg-1]; // sauvegarder le dernier enregistrement du bloc
            /* Décalages intra-bloc */
            for(k = buf.NbEnreg-1; k>j; k--)
                buf.t[k] = buf.t[k-1];
            buf.t[j] = enreg;

            if(buf.NbEnreg < 10000) // si le bloc n'est pas plein, on remet x dans permier indice libre du bloc
            {
                buf.NbEnreg++;
                if (j == buf.NbEnreg-1) // le nouvel enregistrement est le dernier enregistrement du fichier
                    buf.t[buf.NbEnreg-2] = x;
                else // le nouvel enregistrement a été inséré entre deux enregistrements
                    buf.t[buf.NbEnreg-1] = x;
                ecrire_dire_index(f,i,&buf);
                (*nb_ecrireDir)++;
                continu = 0;
            }
            else // si le bloc est plein, x doit être inséré dans un nouveau bloc i+1 à la position 0
            {
                ecrire_dire_index(f,i,&buf);
                (*nb_ecrireDir)++;
                i++;
                j = 0;
                enreg = x; // l'enregistrement qui doit être inséré à l'emplacement (i,0)
            }
        }
        // si on dépasse la fin de fichier, on rajoute un nouveau bloc contenant un seul enregistrement
        if (i>en_tete_index(f,1))
        {
            init_bloc_index(&buf);
            buf.t[0] = enreg;
            buf.NbEnreg = 1;
            ecrire_dire_index(f,en_tete_index(f,1)+1,&buf);
            (*nb_ecrireDir)++;
        }
        af_entete_index(f,2,en_tete_index(f,2)+1); /* incrémenter le champ de l'entête qui contient le nombre d'enregistrements */
        return 1;
    }
}


///********************MODULES D'AFFICHAGE**************/
/********************** Affichage entete **************/

void affichage_entete(LNOF *fichier,char nom_fich[])//afficher les caracteristiques de fichier
{ouvrir(fichier,nom_fich,'a');//ouvrir le fichier en mode ancien
if(fichier->f)//si le fichier existe on affiche toutes les caracteristiques
    {printf("\n\t\tAFFICHAGE EN_TETE");
    printf("\n\t***Numero du premier bloc=%d",en_tete(fichier,1));
    printf("\n\t***Le nombre des enregistrements=%d",en_tete(fichier,2));
    printf("\n\t***Numero du dernier bloc=%d",en_tete(fichier,3));}
    fermer(fichier);
}

/******************Affichage entete de l'index**********/
void affichage_entete_index(TOF *fichier,char nom_fich[])//afficher les caracteristiques de fichier
{ouvrir_index(fichier,nom_fich,'a');//ouvrir le fichier en mode ancien
if(fichier->f){//si le fichier existe on affiche toutes les caracteristiques
    printf("\n\t\tAFFICHAGE EN_TETE INDEX");
    printf("\n\t***Le nombre des enregistrements=%d",en_tete_index(fichier,1));
    printf("\n\t***Numero du dernier bloc=%d",en_tete_index(fichier,2));}
    fermer_index(fichier);
}


///**Consulter les enregistrement selon l'age et la region***///
void Affichage_selon_region_age(LNOF *fichier,char nom_fich[],int age_min, int age_max, int region_militaire){
    TBloc Buffer;
    ouvrir(fichier,nom_fich,'a');
    int i=1,j=0,temp;

    while (i<=en_tete(fichier,3)){
        lire_dire(fichier,i,&Buffer);
        while (j < 100){

        temp = Buffer.t[j].date_de_nais[0] ;
        if(temp<=(2022 - age_min) && temp >=(2022 - age_max) && region_militaire == Buffer.t[j].region_melit ){
            //printf(" j=%d \n",j);
            printf("Le matricule : %d\n",Buffer.t[j].matricule);
            printf("Le nom : %s\n",Buffer.t[j].nom);
            printf("Le prenom : %s\n",Buffer.t[j].prenom);
            printf("La date de naissance : %d/%d/%d \n",Buffer.t[j].date_de_nais[0],Buffer.t[j].date_de_nais[1],Buffer.t[j].date_de_nais[2]);
            printf("La wilaya de naissance :");
            Affichage_caractere("DB_Wilaya_Naissance.txt",Buffer.t[j].wilaya_nais);
            printf("\nLe groupe sanguin :");
            Affichage_caractere("DB_Groupe_Sanguin.txt",Buffer.t[j].groupe_sang);
            printf("\nLe grade :");
            Affichage_caractere("DB_Grade.txt",Buffer.t[j].grade);
            printf("\nLa force arme :");
            Affichage_caractere("DB_Force_Armée.txt",Buffer.t[j].force_arme);
            printf("\nLa region militaire :");
            Affichage_caractere("DB_Région_militaire.txt",Buffer.t[j].region_melit);
                     printf("\nEFFACE : %d",Buffer.t[j].efface );
            printf("\n--------------------------------\n");
        }
        j++;
        }
        i++;
        j=0;
        }
}
///*************************************************************************************
///*************************************************************************************
void Affichage_selon_grade(LNOF *fichier,char nom_fich[],int choice){
    switch(choice){
    case 1:
        Affichage_selon_grade_second(fichier,nom_fich,1,2,3,3);
        break;
    case 2:
        Affichage_selon_grade_second(fichier,nom_fich,4,5,6,6);
        break;
    case 3:
        Affichage_selon_grade_second(fichier,nom_fich,7,8,9,10);
        break;
    case 4:
        Affichage_selon_grade_second(fichier,nom_fich,11,12,13,14);
        break;
    case 5:
        Affichage_selon_grade_second(fichier,nom_fich,15,16,17,17);
        break;
        default: printf("Choix errone");
}

}
///***********************************************************************************
void Affichage_selon_grade_second(LNOF *fichier,char nom_fich[],int a,int b,int c,int d){
    TBloc Buffer;
    ouvrir(fichier,nom_fich,'a');
    int i=1,j=0,temp;

    while (i <= en_tete(fichier,3)){
        lire_dire(fichier,i,&Buffer);
        while (j < 100){
        temp = Buffer.t[j].grade ;
        //printf("hehe :%d\n",temp);
        if(Buffer.t[j].grade== a ||Buffer.t[j].grade== b ||Buffer.t[j].grade== c||Buffer.t[j].grade== d){
            printf("Le matricule : %d\n",Buffer.t[j].matricule);
            printf("Le nom : %s\n",Buffer.t[j].nom);
            printf("Le prenom : %s\n",Buffer.t[j].prenom);
            printf("La date de naissance : %d/%d/%d \n",Buffer.t[j].date_de_nais[2],Buffer.t[j].date_de_nais[1],Buffer.t[j].date_de_nais[0]);
            printf("La wilaya de naissance :");
            Affichage_caractere("DB_Wilaya_Naissance.txt",Buffer.t[j].wilaya_nais);
            printf("\nLe groupe sanguin :");
            Affichage_caractere("DB_Groupe_Sanguin.txt",Buffer.t[j].groupe_sang);
            printf("\nLe grade :");
            Affichage_caractere("DB_Grade.txt",Buffer.t[j].grade);
            printf("\nLa force arme :");
            Affichage_caractere("DB_Force_Armée.txt",Buffer.t[j].force_arme);
            printf("\nLa region militaire :");
            Affichage_caractere("DB_Région_militaire.txt",Buffer.t[j].region_melit);
            printf("\n-----------------------------------------------\n");
        }
        j++;
        }
        i++;
        j=0;
        }
        fermer(fichier);
}
///**********************Affichage des n premier blocs***********************
void Affichage_N_premier_bloc(LNOF *fichier,char nom_fich[],int n){
    TBloc Buffer;
    ouvrir(fichier,nom_fich,'a');
    int i=1,j=0;
    while (i<= n){
        lire_dire(fichier,i,&Buffer);
        while (j < 100){
            printf("Le matricule : %d\n",Buffer.t[j].matricule);
            printf("Le nom : %s\n",Buffer.t[j].nom);
            printf("Le prenom : %s\n",Buffer.t[j].prenom);
            printf("La date de naissance : %d/%d/%d \n",Buffer.t[j].date_de_nais[0],Buffer.t[j].date_de_nais[1],Buffer.t[j].date_de_nais[2]);
            printf("La wilaya de naissance :");
            Affichage_caractere("DB_Wilaya_Naissance.txt",Buffer.t[j].wilaya_nais);
            printf("\nLe groupe sanguin :");
            Affichage_caractere("DB_Groupe_Sanguin.txt",Buffer.t[j].groupe_sang);
            printf("\nLe grade :");
            Affichage_caractere("DB_Grade.txt",Buffer.t[j].grade);
            printf("\nLa force arme :");
            Affichage_caractere("DB_Force_Armée.txt",Buffer.t[j].force_arme);
            printf("\nLa region militaire :");
            Affichage_caractere("DB_Région_militaire.txt",Buffer.t[j].region_melit);
            printf("\nEFFACE : %d ",Buffer.t[j].efface );
            printf("\n--------------------------------\n");
        j++;
        }
        i++;
        j=0;
        }
printf("\nAFFICHAGE TERMINE");
}


/***Affiche les champs des enregistrements avec des caracteres***/

void Affichage_caractere(const char nom_fichier_donne[], int numero ){
int i=0 ;
char donne[60];
FILE * f;

f = fopen(nom_fichier_donne,"r+");  // le fichier de donne ".txt"
rewind(f);

while (numero != i){
    fgets(donne,60,f);
    i++;
}
char line[60];  // where we will put a copy of the input
char *subString; // the "result"

strcpy(line,donne);
subString = strtok(line,":"); // find the first double quote
subString=strtok(NULL,",");   // find the second double quote

printf("%s",subString);
fclose(f);
}

/****************affichage du menu***************/
void menu_principal(){
 textcolor(WHITE);
 //printf("\n\t\t\tMENU DEMONSTRATION");
printf("\n          ___                    ___                    ___                    ___          ");
printf("\n         /\\    \\                  /\\    \\                  /\\    \\                  /\    \\         ");
printf("\n        /::\\____\\                /::\\    \\                /::\\____\\                /::\____\\           ");
printf("\n       /::::|   |               /::::\\    \\              /::::|   |               /:::/    /              ");
printf("\n      /:::::|   |              /::::::\\    \\            /:::::|   |              /:::/    /                 ");
printf("\n     /::::::|   |             /:::/\\:::\\    \\          /::::::|   |             /:::/    /                  ");
printf("\n    /:::/|::|   |            /:::/__\\:::\\    \\        /:::/|::|   |            /:::/    /                   ");
printf("\n   /:::/ |::|   |           /::::\\   \\:::\\    \\      /:::/ |::|   |           /:::/    /                    ");
printf("\n  /:::/  |::|___|______    /::::::\\   \\:::\\    \\    /:::/  |::|   | ___    /:::/    /      ___          ");
printf("\n /:::/   |::::::::\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/   |::|   |/\\    \\  /:::/____/      /\\    \\         ");
printf("\n/:::/    |:::::::::\\____\\/:::/__\\:::\\   \\:::\\____\\/:: /    |::|   /::\\____\\|:::|    /      /::\\____\\        ");
printf("\n\\::/    / ~~~~~/:::/    /\\:::\\   \\:::\\   \\::/    /\\::/    /|::|  /:::/    /|:::|____\\     /:::/    /        ");
printf("\n \\/____/      /:::/    /  \\:::\\   \\:::\\   \\/____/  \\/____/ |::| /:::/    /  \\:::\\    \\   /:::/    /         ");
printf("\n             /:::/    /    \\:::\\   \\:::\\    \\              |::|/:::/    /    \\:::\\    \\ /:::/    /          ");
printf("\n            /:::/    /      \\:::\\   \\:::\\____\\             |::::::/    /      \\:::\\    /:::/    /           ");
printf("\n           /:::/    /        \\:::\\   \\::/    /             |:::::/    /        \\:::\\__/:::/    /            ");
printf("\n          /:::/    /          \\:::\\   \\/____/              |::::/    /          \\::::::::/    /             ");
printf("\n         /:::/    /            \\:::\\    \\                  /:::/    /            \\::::::/    /              ");
printf("\n        /:::/    /              \\:::\\____\\                /:::/    /              \\::::/    /               ");
printf("\n        \\::/    /                \\::/    /                \\::/    /                \\::/____/                ");
printf("\n         \\/____/                  \\/____/                  \\/____/                  ~~                      ");
 textcolor(GREEN);
 printf("\n\t");
 printf("\n\t 1. creation du fichier PERSONNEL-ANP_DZ.bin");
 printf("\n\t 2. Insertion d'un nouvel enregistrement au fichier.");
 printf("\n\t 3. Modification de la région militaire d'un enregistrement.");
 printf("\n\t 4. Supprimer un enregistrement donne par le matricule.");
 printf("\n\t 5. Supprimer tous les enregistrements relatifs a une force armee.");
 printf("\n\t 6. Consulter tous les enregistrements relatifs a region militaire donnee ayant un age entre deux valeurs");
 printf("\n\t 7. Consulter tous les enregistrements appartenant a une categorie de grades donnee");
 printf("\n\t 8. Fragmenter le fichier principal en 6 fichiers contenant les enregistrements relatifs a une region militaire.");
 printf("\n\t 9. Afficher le nombre de lecture et d'ecriture et quitter le programme ");
}

void menu_grade(){
 printf("\n\tChoisissez l'une des categories de grades suivantes :");
 printf("\n\t\t 1. Officiers-généraux");
 printf("\n\t\t 2. Officiers-supérieurs");
 printf("\n\t\t 3. Officiers");
 printf("\n\t\t 4. Sous-officiers");
 printf("\n\t\t 5. Hommes de troupes\n");
 }

void Clear_screen(){system("cls");}


void textcolor(unsigned int color) //une fonction pour definir la couleur du texte
{   if (color >15 || color <=0)
    { HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hcon,15);
    }
    else
    {HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hcon,color);
    }
}

void textbackground(int bcolor) // une fonction pour definir la couleur de l'arriere plan du texte
{    WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {wColor = (csbi.wAttributes & 0xF) | ((bcolor  << 4 ) & 0xF0);
      SetConsoleTextAttribute(hStdOut, wColor);
     }
}

void color(int t,int f) // une Fonction pour changer les couleurs ( Texte / Arrière plan) */
{  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(H,f*16+t);
}


void Image_te3_Esi_tclignioti (int num )
{
    system("color 01") ; //dark background
  if(num%2==0) // nombre pair
  { textcolor(LIGHTCYAN) ;
    printf("\n\t        _" ) ;
    printf("\n\t       |_|" ) ;
    printf("\n\t       /_/" ) ;
    textcolor(CYAN) ;
    printf("\n   ______  _____ _____ ") ;
    printf("\n  |  ____|/ ____|_   _|") ;
    printf("\n  | |__  | (___   | | ") ;
    printf("\n  |  __|  \___ \  | | ") ;
    printf("\n  | |____ ____) |_| |_") ;
    printf("\n  |______|_____/|_____|") ;

  }
  if(num%2!=0) // nombre impair
  {
    textcolor(LIGHTCYAN) ;
    printf("\n\t        _" ) ;
    printf("\n\t       |_|" ) ;
    printf("\n\t       /_/" ) ;
    textcolor(WHITE) ;

    printf("\n   ______  _____ _____ ") ;
    printf("\n  |  ____|/ ____|_   _|") ;
    printf("\n  | |__  | (___   | | ") ;
    printf("\n  |  __|  \___ \  | | ") ;
    printf("\n  | |____ ____) |_| |_") ;
    printf("\n  |______|_____/|_____|") ;
  }

}


void Animation_tank(int num)
{
    system("color 01") ;

    if(num==0)
    {textcolor(GREEN);
    printf("\n    [ O ]") ;
    printf("\n      \\ \\      p") ;
    printf("\n       \\ \\  \\o/") ;
    printf("\n        \\ \\--'---_") ;
    printf("\n        /\\ \\   / ~~\\_") ;
    printf("\n  ./---/__|=/_/------//~~~\\") ;
    printf("\n /___________________/O   O \\") ;
    printf("\n (===(\\_________(===(Oo o o O)   ") ;
    printf("\n  \\~~~\\____/     \\---\\Oo__o--") ;
    printf("\n    ~~~~~~~       ~~~~~~~~~~") ;
    }

    if(num==1)
    {textcolor(GREEN);
    printf("\n      [ O ]") ;
    printf("\n        \\ \\      p") ;
    printf("\n         \\ \\  \\o/") ;
    printf("\n          \\ \\--'---_") ;
    printf("\n          /\\ \\   / ~~\\_") ;
    printf("\n    ./---/__|=/_/------//~~~\\") ;
    printf("\n   /___________________/O   O \\") ;
    printf("\n   (===(\\_________(===(Oo o o O)   ") ;
    printf("\n    \\~~~\\____/     \\---\\Oo__o--") ;
    printf("\n      ~~~~~~~       ~~~~~~~~~~") ;
    }

    if(num==2)
    {textcolor(GREEN);
    printf("\n\t    [ O ]") ;
    printf("\n\t      \\ \\      p") ;
    printf("\n\t       \\ \\  \\o/") ;
    printf("\n\t        \\ \\--'---_") ;
    printf("\n\t        /\\ \\   / ~~\\_") ;
    printf("\n\t  ./---/__|=/_/------//~~~\\") ;
    printf("\n\t /___________________/O   O \\") ;
    printf("\n\t (===(\\_________(===(Oo o o O)   ") ;
    printf("\n\t  \\~~~\\____/     \\---\\Oo__o--") ;
    printf("\n\t    ~~~~~~~       ~~~~~~~~~~") ;
    }

    if(num==3)
    {textcolor(GREEN);
    printf("\n\t      [ O ]") ;
    printf("\n\t        \\ \\      p") ;
    printf("\n\t         \\ \\  \\o/") ;
    printf("\n\t          \\ \\--'---_") ;
    printf("\n\t          /\\ \\   / ~~\\_") ;
    printf("\n\t    ./---/__|=/_/------//~~~\\") ;
    printf("\n\t   /___________________/O   O \\") ;
    printf("\n\t   (===(\\_________(===(Oo o o O)   ") ;
    printf("\n\t    \\~~~\\____/     \\---\\Oo__o--") ;
    printf("\n\t      ~~~~~~~       ~~~~~~~~~~") ;
    }

    if(num==4)
    {textcolor(GREEN);
    printf("\n\t\t    [ O ]") ;
    printf("\n\t\t      \\ \\      p") ;
    printf("\n\t\t       \\ \\  \\o/") ;
    printf("\n\t\t         \\ \\--'---_") ;
    printf("\n\t\t         /\\ \\   / ~~\\_") ;
    printf("\n\t\t   ./---/__|=/_/------//~~~\\") ;
    printf("\n\t\t  /___________________/O   O \\") ;
    printf("\n\t\t  (===(\\_________(===(Oo o o O)   ") ;
    printf("\n\t\t   \\~~~\\____/     \\---\\Oo__o--") ;
    printf("\n\t\t     ~~~~~~~       ~~~~~~~~~~") ;
    }
}


/*-----------------------------------------------------------------------------------------------------------------------------*/
void entree ()
{
    system("cls");
    textcolor(5);
    gotoxy(10,1);printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
    gotoxy(10,2);printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    textcolor(3);
    printf("             _");
    textcolor(15);
    printf("      REPUBLIQUE ALGERIENNE DEMOCRATIQUE ET POPULAIRE ");

    textcolor(5);
    printf("       *\n");
    gotoxy(10,3);printf(" *            ");

    textcolor(3);
    printf("|_|");
    textcolor(15);
    printf("      MINISTERE DE L'ENSEIGNEMENT SUPERIEUR ET DE LA ");
    textcolor(5);
    printf("       *\n");
    gotoxy(10,4);printf(" *           ");
    textcolor(3);
    printf("/_/");
    textcolor(15);
    printf("                   RECHERCHE SCIENTIFIQUE ");
    textcolor(5);
    printf("                   *\n");

    gotoxy(10,5);printf(" *   ");
    textcolor(15);
    printf("___  ___ _");

    textcolor(5);
    printf("                                                              *\n");
    gotoxy(10,6);printf(" *  ");
    textcolor(15);

    printf("/ _ \\/ __| |");

    textcolor(5);
    printf("                                                             *\n");
    gotoxy(10,7);printf(" * ");
    textcolor(15);

    printf("|  __/\\__ \\ |        ECOLE NATIONALE SUPERIEURE D'INFORMATIQUE");

    textcolor(5);
    printf("            *\n");
    gotoxy(10,8);printf(" *  ");
    textcolor(15);

    printf("\\___||___/_|     SRUCTURE DE FICHIERS ET STRUCTURE DE DONNEES");

    textcolor(5);
    printf("            * \n");
    gotoxy(10,9);printf(" *  ");
    textcolor(15);
    printf("                                  -SFSD-");
    textcolor(5);
    printf("                                 *\n");
    gotoxy(10,10);printf(" *  ");
    textcolor(4);
    printf("         --------------------------------------------------------      ");
    textcolor(5);
    printf("  *\n");
    gotoxy(10,11);printf(" *  ");
    textcolor(4);
    printf("         -");
    textcolor(15);
    printf("        Le premier tavail pratique SFSD.");
    textcolor(4);
    printf("           -");
    textcolor(5);
    printf("      *\n");
    gotoxy(10,12);printf(" *  ");
    textcolor(4);
    printf("         -");
    textcolor(15);
    printf(" Le theme est: Etablir une base de donnee de ");
    textcolor(4);
    printf(" -");
    textcolor(5);
    printf("        *\n");
    gotoxy(10,13);printf(" *  ");
    textcolor(4);
    printf("         -");
    textcolor(15);
    printf(  "          l'ARMEE NATIONALE POPULAIRE" );
    textcolor(4);
    printf("               -");
    textcolor(5);
    printf("      *\n");
    gotoxy(10,14);printf(" *  ");
    textcolor(4);
    printf("         -");
    textcolor(15);
    printf(" Realise par: BENABBES ILYES & KEDADSA ISLAM ");
    textcolor(4);
    printf("         -");
    textcolor(5);
    printf("        *\n");
    gotoxy(10,15);printf(" *  ");
    textcolor(4);
    printf("         -");
    textcolor(15);
    printf("     Section: B           Groupe: 04         ");
    textcolor(4);
    printf("         -");
    textcolor(5);
    printf("      *\n");
    gotoxy(10,16);printf(" *  ");
    textcolor(4);
    printf("         -");
    textcolor(15);
    printf(" Encadre par: Dr KERMI ADEL                  ");
    textcolor(4);
    printf("    -");
    textcolor(5);
    printf("        *\n");
    gotoxy(10,17);printf(" *  ");
    textcolor(4);
    printf("         -");
    textcolor(15);
    printf(" Annee Universitaire:   2021/2022            ");
    textcolor(4);
    printf("         -");
    textcolor(5);
    printf("      *\n");
    gotoxy(10,18);printf(" *  ");
    textcolor(4);
    printf("         --------------------------------------------------------      ");
    textcolor(5);
    printf("  *\n");
    textcolor(5);
    gotoxy(10,19);printf(" *                                                                         *\n");
    gotoxy(10,20);printf(" *                                                                           *\n");
    gotoxy(10,21);printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
    gotoxy(10,22);printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");

    textcolor(15);
    printf("\n\n\t\t");
    system("pause");
    textcolor(4);
}


void gotoxy(int xpos, int ypos)
{
        COORD scrn;
        HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

        scrn.X = xpos-1;
        scrn.Y = ypos;
        SetConsoleCursorPosition(hOuput, scrn);
}


void sortie ()
{
    system("cls");
    textcolor(10);
    gotoxy(10,1);printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
    gotoxy(10,2);printf("  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    gotoxy(10,3);printf(" *                                                                            *\n");
    gotoxy(10,4);printf("  *                                                                          *\n");
    gotoxy(10,5);printf(" *                                                                            *\n");
    gotoxy(10,6);printf("  *                                                                          *\n");
    gotoxy(10,7);printf(" *                                                                            *\n");
    gotoxy(10,8);printf("  *           Le programme va se quitter dans un instant...                  * \n");
    gotoxy(10,9);printf(" *                                                                            *\n");
    gotoxy(10,10);printf("  *                                                                          *\n");
    gotoxy(10,11);printf(" *           MERCI POUR VOTRE UTILISATION DE NOTRE PROGRAMME                  *\n");
    gotoxy(10,12);printf("  *                                                                          *\n");
    gotoxy(10,14);printf("  *                                                                          *\n");
    gotoxy(10,15);printf(" *                                                                            *\n");
    gotoxy(10,16);printf(" * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
    gotoxy(10,17);printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");

    textcolor(15);
}


void soldats(){
      textcolor(10);
gotoxy(20,20);printf("\n    |\                |\                |\                |\  ");
gotoxy(20,21);printf("\n    || .---.          || .---.          || .---.          || .---.  ");
gotoxy(20,22);printf("\n    ||/_____\         ||/_____\         ||/_____\         ||/_____\  ");
gotoxy(20,23);printf("\n    ||( '.' )         ||( '.' )         ||( '.' )         ||( '.' )    ");
gotoxy(20,24);printf("\n    || \\_-_/_         || \\_-_/_         || \\_-_/_         || \\_-_/_   ");
gotoxy(20,25);printf("\n    :- 'V'//-.       :- 'V'//-.       :- 'V'//-.       :- 'V'//-.   ");
gotoxy(20,26);printf("\n   / ,   |// , `\    / ,   |// , `\    / ,   |// , `\    / ,   |// , `\   ");
gotoxy(20,27);printf("\n  / /|Ll //Ll|| |   / /|Ll //Ll|| |   / /|Ll //Ll|| |   / /|Ll //Ll|| |   ");
gotoxy(20,28);printf("\n /_/||__//   || |  /_/||__//   || |  /_/||__//   || |  /_/||__//   || |   ");
gotoxy(20,29);printf("\n \\ \\/---|[]==|| |  \\ \\/---|[]==|| |  \\ \\/---|[]==|| |  \\ \\/---|[]==|| |  ");
gotoxy(20,30);printf("\n  \\/\\__/ |   \\| |   \\/\\__/ |   \\| |   \\/\\__/ |   \\| |   \\/\\__/ |   \\| | ");
gotoxy(20,31);printf("\n  /\\|_   | Ll_\\ |   /|/_   | Ll_\\ |   /|/_   | Ll_\\ |   /|/_   | Ll_\\ |  ");
gotoxy(20,32);printf("\n  `--|`^'''^`||_|   `--|`^'''^`||_|   `--|`^'''^`||_|   `--|`^'''^`||_|   ");
gotoxy(20,33);printf("\n     |   |   ||/       |   |   ||/       |   |   ||/       |   |   ||/  ");
gotoxy(20,34);printf("\n     |   |   |         |   |   |         |   |   |         |   |   | ");
gotoxy(20,35);printf("\n     |   |   |         |   |   |         |   |   |         |   |   |");
gotoxy(20,36);printf("\n     |   |   |         |   |   |         |   |   |         |   |   |");
gotoxy(20,37);printf("\n     L___l___J         L___l___J         L___l___J         L___l___J");
gotoxy(20,38);printf("\n      |_ | |           | | |           | | |           | | _|");
gotoxy(20,39);printf("\n     (__|__)         (__|__)         (__|__)         (__|__)");
gotoxy(20,40);printf("\n      ^^^ ^^^           ^^^ ^^^           ^^^ ^^^           ^^^ ^^^");

}


