#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"
#include<string.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
 TEnreg new_enreg ;
 TEnrindex new_enreg_index ;
 int nblire=0 , nbecrire=0 ;
TOF fx ;
TOF * fich_index = &fx ;
LNOF fichier ;
LNOF * mon_fich = &fichier;
LNOF fichier1 ;
LNOF * mon_fich1 = &fichier1;
LNOF fichier2 ;
LNOF * mon_fich2 = &fichier2;
LNOF fichier3 ;
LNOF * mon_fich3 = &fichier3;
LNOF fichier4 ;
LNOF * mon_fich4 = &fichier4;
LNOF fichier5 ;
LNOF * mon_fich5 = &fichier5;
LNOF fichier6 ;
LNOF * mon_fich6 = &fichier6;
TBloc buff ;
int nbenreg ;
char nom_fich[30]="PERSONNEL-ANP_DZ.bin";


 int main()
{
    TableIndex * Tableau = calloc(1,sizeof(TableIndex));
    TableIndex * Tab =calloc(1,sizeof(TableIndex));
int choice=0;
entree();
while(choice!=8)
{
 Clear_screen();
 printf("\n\n");
 textcolor(GREEN);
 menu_principal();
textcolor(WHITE);
 printf("\n\n Enter Your CHOICE: ");
 scanf("%d",&choice);
 switch(choice)
 {

  case 1:     printf("\n Donnez le nombre de enregs a creer:");
              scanf("%d",&nbenreg);
              creation_du_fichier(mon_fich,nom_fich,nbenreg,Tableau,&nblire,&nbecrire);
              printf("\nLe fichier PERSONNEL-ANP_DZ.bin a ete cree avec succes");
              printf("\nLe fichier d'INDEX a ete cree avec succes");
              affichage_entete(mon_fich,nom_fich);
              printf("\n Voulez vous afficher le fichier ?");

              int choice1 = 0;
              while(choice1!= 1 && choice1!= 2 ){
                    printf("\n\tChoisissez une opertation");
                    printf("\n\t\t 1. OUI");
                    printf("\n\t\t 2. NON\n");
                    scanf("%d",&choice1);
                    int n = 0;
                    switch(choice1){
                    case 1 :
                        printf("\nCombien de bloc voulez vous afficher ?\n");
                        scanf("%d",&n);
                        Affichage_N_premier_bloc(mon_fich,nom_fich,n);
                                break;
                    case 2 :    break;
                    default : printf("\nChoix invalide");
                                break;
                    }
              }
              break;

  case 2:

  printf("\n le nom : ");
  char name[30],prenom[30];
  scanf("%s",name);
  printf("\n name is %s", name);
  strcpy(new_enreg.nom  ,   name);
  printf("\n le prenome : ");
  scanf("%s",prenom);
  strcpy(new_enreg.prenom, prenom);
  printf("\n le matricule: ");
  scanf("%d",&new_enreg.matricule);
  printf(" le matrciule de enr.mat= %d",new_enreg.matricule);
     new_enreg.grade = 1;
     new_enreg.groupe_sang = 1 ;
     new_enreg.region_melit =  2 ;
     new_enreg.wilaya_nais = 5 ;
     new_enreg.efface = 0 ;
     new_enreg.date_de_nais[0] = 1995 ;
     new_enreg.date_de_nais[1] = 5 ;
     new_enreg.date_de_nais[2] = 26 ;
     int blclof , deplof ;
     insertion_LNOF(mon_fich,nom_fich,&new_enreg,&blclof,&deplof);
     nblire++;
     nbecrire++;
     printf("\n blclof=%d \t deplof=%d",blclof,deplof);
      new_enreg_index.efface = 0 ;
      new_enreg_index.matricule = new_enreg.matricule;
      new_enreg_index.num_bloc = blclof;
      new_enreg_index.pos_bloc = deplof ;

      ouvrir_index(fich_index,"Fichier_Index_officiel.bin",'a');

     insertion_TOF(fich_index,new_enreg_index,&nblire,&nbecrire);
     fermer_index(fich_index);

              break;
  case 3:
              modif_reg_melit(mon_fich,fich_index,nom_fich,"Fichier_Index_officiel.bin",&nblire,&nbecrire);

              break;
  case 4:
              suprim_enreg(mon_fich,fich_index,nom_fich,"Fichier_Index_officiel.bin");

              break;
  case 5:
              printf("\nYOU SELECTED OPTION 5\n");
              sup_selon_force(mon_fich,nom_fich,fich_index,"Fichier_Index_officiel.bin",&nblire,&nbecrire);
              break;
  case 6:
              printf("\nDonnez la plage d'age a recherche\n");
              int min =0, max=0;
              printf("Entre :");
              scanf("%d",&min);
              printf("et :");
              scanf("%d",&max);
              printf("\nDonnez le numero de la region que vous voulez affiche\n");
              int Nb = 0;
              scanf("%d",&Nb);
              Affichage_selon_region_age(mon_fich,nom_fich,min,max,Nb,&nblire,&nbecrire);

              break;
  case 7:
              printf("\nVeuillez entrer la categorie de grade a afficher\n");
              menu_grade();
              Nb=0;
              scanf("%d",&Nb);
              Affichage_selon_grade(mon_fich,nom_fich,Nb);
              break;
  case 8:
              Fragmentation(mon_fich,nom_fich,mon_fich1,mon_fich2,mon_fich3,mon_fich4,mon_fich5,mon_fich6);
              break;

  case 9:     printf("Le nombre de lecture egale a %d et le nombre d'ecriture egale a",nblire , nbecrire );
              Clear_screen();
              sortie();
              printf("\n");
              soldats();
              return 0;
  otherwise:
             printf("\nINVALID SELECTION...Please try again");
  }
  getch();
}

   return 0;


}



