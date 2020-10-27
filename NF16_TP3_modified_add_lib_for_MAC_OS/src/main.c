#include <stdio.h>
#include "../include/TP3.h"
#include <stdlib.h>



int main(void) {

    T_Patient* listepatients;
   
    fflush(stdin);
    //ajouterPatient(listepatients,7, "Viera", "Baptiste");
    //ajouterPatient(listepatients,2, "Dupont", "Pierre");


    int choix;

    do
   {

      /* affichage menu */
        printf("\n---------------MENU---------------\n");
      printf("\n1: Créer une instance à partir d’un         fichier\n"
             "2: Afficher tous les patients et leurs rendez-vous\n"
             "3: Afficher tous les soigneurs et leurs intervalles de temps disponibles\n"
             "4: Afficher un rendez-vous en indiquant l’identifiant du patient et le soigneur correspondant\n"
             "5: Modifier un rendez-vous en indiquant l’identifiant du patient et celui du soigneur correspondant\n"
             "6: Supprimer un rendez-vous en indiquant l’identifiant du patient et celui du soigneur correspondant\n"
             "7: Ordonnancer\n"
             "8: Exporter la solution d’un ordonnancement\n"
             "9: Quitter\n");
 
      fflush(stdin);
      printf("\nVotre choix ? ");
      scanf("%d",&choix);
 
      switch(choix)
      {
         case 1:
            break;
 
         case 2:
            /*affichage_Patients(listepatients);*/
            break;
 
         case 3:

            break;
 
         case 4:
            break;
        
        case 5:
            // Création d'un fichier binaire qui contient l'ensemble des voitures du parc
            /*printf("Quel est le nom du fichier binaire qui contiendra votre parc de voitures? " );
            scanf("%s",nomfileparc); 
            saveParc(nomfileparc, voitures,n);*/
            break;
        
        case 6:
            break;

        case 7:
            break;

        case 8:
            break;
        
        case 9:
            break;        

        default:
            printf("Choix erroné\n");
      }
   }while(choix!=9);

    return 0;
}





    /*T_soigneur* listeSoigneurs;

    ajouterSoigneur(listeSoigneurs,idSoi, nom,prenom);

    T_Patient* ajouterPatient(T_Patient* listePatients, Index_Patient idPat, char* nom, char* prenom)

    T_RendezVous* ajouterRendezVous(T_RendezVous* listeRendezVous, int idSoi, int dateDebutSouaitee, int dateFinSouaitee, int tempsDeplacement, char* desc)

    void modifierRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc)

    T_RendezVous* supprimerRendezVous(T_RendezVous* listeRdV, Index_Patient idSoi){*/



