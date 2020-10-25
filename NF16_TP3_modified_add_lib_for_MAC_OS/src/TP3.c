/****************************************************************
Author: Chenghao WANG
Contact: chenghao.wang@hds.utc.fr
Institute: Heudiasyc, université de technologie de compiègne
Date: 12/10/2020
*****************************************************************/
#include "../include/TP3.h"

/**
 * @brief Ajout d’un soigneur, où la liste des intervalles de temps disponibles pour un nouveau soigneur
 * est initialisée avec un seul intervalle [0, inf[.
 * @param listeSoigneurs une liste de soigneurs laquelle ne doit pas être vide.
 * @param idSoi un identifiant d'un soigneur.
 * @param nom le nom d'un sogineur.
 * @param prenom le prénom d'un soigneur.
 */
T_Soigneur* ajouterSoigneur(T_Soigneur* listeSoigneurs, Index_Soigneur idSoi, char* nom, char* prenom){

    T_Soigneur* soigneur;
    soigneur=malloc(sizeof(T_Soigneur));
    soigneur->id_soi = idSoi;
    soigneur->nom = nom;
    soigneur->prenom = prenom;
    soigneur->suivant = listeSoigneurs;
    return soigneur;

}

/**
 * @brief Ajout d'un patient, où la liste de rendez-vous médicaux pour un nouveau patient est initialement vide.
 * @param listePatients une liste de patients laquelle ne doit pas être vide.
 * @param idPat un identifiant d'un patient.
 * @param nom le nom d'un patient.
 * @param prenom le prénom d'un patient.
 */
T_Patient* ajouterPatient(T_Patient* listePatients, Index_Patient idPat, char* nom, char* prenom){
    T_Patient* patient;
    patient=malloc(sizeof(T_Soigneur));
    patient->id_pat = idPat;
    patient->nom = nom;
    patient->prenom = prenom;
    patient->suivant = listePatients;
    return patient;
 
}
/**
 * @brief Ajout d’un rendez-vous médical pour un patient.
 * @param listeRdV une liste de Rendezvous laquelle ne doit pas être vide.
 * @param idSoi un identifiant d'un soigneur associé.
 * @param dateDebutSouhaitee  la date de début souhaitée d'un RdV.
 * @param dateFinSouhaitee  la date de fin souhaitée d'un RdV.
 * @param tempsDeplacement la temps de déplacement depuis un RdV précédent.
 * @param desc une discription brève.
 */

 T_RendezVous* ajouterRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc)
{
    T_RendezVous* rendezvous;
    rendezvous = malloc(sizeof(T_RendezVous));
    rendezvous -> id_soi = idSoi;
    rendezvous -> debut_souhaitee = dateDebutSouhaitee;
    rendezvous -> fin_souhaitee = dateFinSouhaitee;
    rendezvous -> temps_deplacement = tempsDeplacement;
    rendezvous -> desc = desc;
    rendezvous -> suivant = listeRdV;
    return rendezvous;
}
/**
 * @brief Modification d’ un rendez-vous médical pour un patient par une date, le temps de déplacement ou une description nouvelle :
 * @param listeRdV une liste de Rendezvous laquelle ne doit pas être vide.
 * @param idSoi un identifiant d'un patient associé.
 * @param dateDebutSouhaitee la datesoigneurut souhaitée d'un RdV.
 * @param dateFinSouhaitee la date de fin souhaitée d'un RdV.
 * @param tempsDeplacement la temps de déplacement depuis un RdV précédent.
 * @param desc une discription brève.
 */
void modifierRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){
  
  T_RendezVous *rdv = listeRdV;
  while (rdv != NULL && rdv->id_soi != idSoi){
    rdv = rdv->suivant;
  }
  rdv->debut_souhaitee = dateDebutSouhaitee;
  rdv->fin_souhaitee = dateFinSouhaitee;
  rdv->temps_deplacement = tempsDeplacement;
  rdv->temps_deplacement = tempsDeplacement;
	
}
/**
 * @brief Suppression d’un rendez-vous médical pour un patient en donnant l’identifiant du patient correspondant.
 * Si un rendez-vous, ni premier ni dernier, est enlevé, le temps de déplacement du traitemsoigneurvant doit être mis à jour.
 * Par exemple, un patient ayant trois rendez-vous : rendez-vous 1 chez le patient A,
 * rendez-vous 2 chez le patient B et rendez-vous 3 chez le patient C, tempsoigneurplacement de 1 à 2 de 30 mn,
 * temps de déplacement dsoigneur de 40 mn, le temps de déplasoigneurde 1 à 3 est défini
 * par sqrt(30^2+40^2)=50mn quand le rendez-vous 2 est supprimé.
 * @param listeRdV une liste de RdV.
 * @param idSoi identifiant d'un patient.
 * @return un pointeur vers la têsoigneura liste de RdV médicaux après une suppression.
 */
T_RendezVous* supprimerRendezVous(T_RendezVous* listeRdV, Index_Patient idSoi){
    
    T_RendezVous* rdvpred,*rdvsucc;
    int trouv=0;
    if (listeRdV==NULL)
    {
       printf("Il n'y pas de rendez-vous ");
    }
    
    else 
    {

        if (listeRdV->id_soi == idSoi)
        {
            rdvsucc = listeRdV;
            listeRdV=listeRdV->suivant;
            free(rdvsucc);
        }

        else
        {
            rdvpred=listeRdV; // prédécesseur
            rdvsucc=listeRdV->suivant;

            while (rdvsucc!=NULL && trouv==0 )
            {
                if (rdvsucc->id_soi==idSoi)
                {
                    trouv=1;
                }
                
                else
                {
                    rdvpred=rdvsucc;
                    rdvsucc=rdvsucc->suivant;
                }
            }

            if (trouv==0)
            {
                printf("Le rendez-vous n'existe pas  ");
            }
            
            else
            {
                rdvpred->suivant=rdvsucc->suivant;
                free(rdvsucc);
            }
        }
    }
    return listeRdV;
}


/**
 * @brief Afficher tous les patients et leurs intervalles de temps disponibles
 * @param listepatients une soigneure patients.
 */
void affichage_patients(T_Patient* listepatients){
   
 // vérifier si pas de modif
   
   //return provSoigneurfichSoigneurients(lSoigneurients);
}

/**
 * @brief Afficher tous les patients et leurs rendez-vous
 * @param listePatients une liste de patients.
 */
void provided_affichage_Patients(T_Patient* listePatients){

   T_Patient* PatientEnCours;
   T_RendezVous* listeRdv=NULL;
   PatientEnCours = listePatients;
   while (PatientEnCours!=NULL)
   {
       printf("ID patient: %d\n",PatientEnCours->id_pat);
       printf("Nom: %s\n",PatientEnCours->nom);
       printf("Prenom: %s\n",PatientEnCours->prenom);
       listeRdv = PatientEnCours->listeRendezVous;
       if (listeRdv!=NULL)
       {
           printf("Date de début affectée en minutes: %d\n ",listeRdv->debut_affectee);
           printf("Date de fin affectée en minutes: %d\n",listeRdv->fin_affectee);
           printf("ID soignant: %d\n",listeRdv->id_soi);
       }
       PatientEnCours=PatientEnCours->suivant;
       printf("\n");
   }
    //return provided_affichage_Patients(listePatients);
}

/**
 * @brief Afficher un rendez-vous en indiquant l’identifiant du patient et le patient correspondant
 * @param listePatients une liste de patientssoigneur
 * @param idPat identifiant d'un patient assoicié d'un RdV à chercher.
 * @param idSoi identifiant d'un patient assoicié d'un RdV à chercher.
 */
void provided_affichage_RendezVous(T_Patient* listePatients, Index_Patient idPat, Index_Patient idSoi){
    //return provided_affichage_RendezVous(listePatients, idPat, idSoi);
}

/**
 * @brief Créer une instance de l’ordonnancement en important à partir d’un fichier.
 * @param filename le nom d'un fichier importé.
 * @return un pointeur vers l’instance.
 */
T_Ordonnancement* creerInstance(char* filename){
     return provided_creerInstance(filename);
 }

/**
 * @brief Affectation d’un rendez-vous en fonction des intervalles de temps disponibles d’un patient
 * (mettre à jour la date de début affectée et la date de fin affectée du rendez-vous ) soigneur
 * @param rdv un RdV.
 * @param patient un patient.
 */
void provided_affecterRdV(T_RendezVous* rdv, T_Soigneur* soigneur){
    //return provided_affecterRdV(rdv, pSoigneur;soigneur
}
/**
 * @brief Ordonnancer les rendez-vous des patients en fonction des intervalles de temps disponibles
 * pour l’ensemble des patients en minimisant la somme des temps d’attente des patients
 * (le temps d’attente soigneurculé par la date de début affectée – la date de début souhaitée).
 * L’algorithme glouton d'ordonnancement en minimisant la somme du temps d’attente des patients se construit comme suit :
 * Étape 1 : Trier les patients par ordre décroissant de durée totale des rendez-vous
 *  (la durée d’un rendez-vous est calculée par la date de fin souhaitée – la date de début souhaitée)
 * Étape 2 : Affecter les rendez-vous des patients dans l’ordre ci-dessus aux intervalles de temps disponible des patients.
 * @param solution un instancesoigneur
 */

void ordonnancer(T_Ordonnancement* solution){
    //return provided_ordonnancer(solution);
}

/**
 * @brief Exporter la solution d’un ordonnancement.
 * Le nom du fichier exporté a sufix de la date de création  d’un ordonnancement, par exemple filename=’solution.txt’,
 * et la date de creation est ‘2020-10-13’, donc le nom de ficher exporté est ‘solution.txt.2020-10-13.txt’.
 * @param solution une solution d'un ordonnancement.
 * @param filename le nom d'un ficher exporté.
 */

void exportSolution(T_Ordonnancement* solution, char* filename){
    //return provided_exportSolution(solution, filename);
}

void menuPrincipal(void){
    //return provided_menu();
}