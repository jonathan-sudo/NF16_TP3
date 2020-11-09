/****************************************************************
Author: Chenghao WANG
Contact: chenghao.wang@hds.utc.fr
Institute: Heudiasyc, université de technologie de compiègne
Date: 12/10/2020
*****************************************************************/
#include "../include/TP3.h"



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  chercher_Patient
 *  Description: 
 *  @brief demande l'ID d'un patient et retourne un pointeur sur le patient correspondant dans la * liste passée en paramètre. Retourne NULL si le patient n'est pas dans la liste.
 *  @param listePatients une liste de patients
 *
 * =====================================================================================
 */

T_Patient* chercher_Patient (T_Patient* listePatients )
{
    Index_Patient idPat;
    T_Patient *PatientEnCours;

    printf("ID du patient?\n");
    scanf("%d",&idPat);
    PatientEnCours = listePatients;
    while(PatientEnCours!=NULL){
        if (PatientEnCours->id_pat==idPat){
            return PatientEnCours;
        }
        PatientEnCours = PatientEnCours->suivant;
    };
    return NULL;

}		/* -----  end of function chercher_Patient  ----- */



/**
 * @brief Ajout d’un soigneur, où la liste des intervalles de temps disponibles pour un nouveau soigneur
 * est initialisée avec un seul intervalle [0, inf[.
 * @param listeSoigneurs une liste de soigneurs laquelle ne doit pas être vide.
 * @param idSoi un identifiant d'un soigneur.
 * @param nom le nom d'un sogineur.
 * @param prenom le prénom d'un soigneur.
 */
T_Soigneur* ajouterSoigneur(T_Soigneur** listeSoigneurs, Index_Soigneur idSoi, char* nom, char* prenom){
    T_Soigneur* soigneur;
    soigneur=malloc(sizeof(T_Soigneur));

    if (soigneur!=NULL)
    {
        soigneur->id_soi = idSoi;
        soigneur->nom = nom;
        soigneur->prenom = prenom;

        soigneur->listeIntervalle=malloc(sizeof(T_Intervalle));
        soigneur->listeIntervalle->debut=0;
        soigneur->listeIntervalle->fin=1440; // 24h


        soigneur->suivant = *listeSoigneurs;
        *listeSoigneurs=soigneur;
        return soigneur;

    }
    else
    {
        return NULL;
    }



    //return provided_ajouterSoigneur(listeSoigneurs, idSoi, nom, prenom);
}
/**
 * @brief Ajout d'un patient, où la liste de rendez-vous médicaux pour un nouveau patient est initialement vide.
 * @param listePatients une liste de patients laquelle ne doit pas être vide.
 * @param idPat un identifiant d'un patient.
 * @param nom le nom d'un patient.
 * @param prenom le prénom d'un patient.
 */
T_Patient* ajouterPatient(T_Patient* *listePatients, Index_Patient idPat, char* nom, char* prenom){
    T_Patient* patient;
    patient=malloc(sizeof(T_Soigneur));
    patient->listeRendezVous=malloc(sizeof(T_RendezVous));
    patient->id_pat = idPat;
    patient->nom = nom;
    patient->prenom = prenom;
    patient->suivant = *listePatients;
    *listePatients=patient;
    return patient;
    //return provided_ajouterPatient(listePatients, idPat, nom, prenom);
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
T_RendezVous* ajouterRendezVous(T_RendezVous* *listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){
    T_RendezVous* rendezvous;
    rendezvous = malloc(sizeof(T_RendezVous));
    rendezvous -> id_soi = idSoi;
    rendezvous -> debut_souhaitee = dateDebutSouhaitee;
    rendezvous -> fin_souhaitee = dateFinSouhaitee;
    rendezvous -> temps_deplacement = tempsDeplacement;
    rendezvous -> desc = desc;
    rendezvous -> suivant = *listeRdV;
    *listeRdV=rendezvous;
    return rendezvous;
    
    //return provided_ajouterRendezVous(listeRdV, idSoi, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement, desc);
}
/**
 * @brief Modification d’ un rendez-vous médical pour un patient par une date, le temps de déplacement ou une description nouvelle :
 * @param listeRdV une liste de Rendezvous laquelle ne doit pas être vide.
 * @param idSoi un identifiant d'un soigneur associé.
 * @param dateDebutSouhaitee la date de début souhaitée d'un RdV.
 * @param dateFinSouhaitee la date de fin souhaitée d'un RdV.
 * @param tempsDeplacement la temps de déplacement depuis un RdV précédent.
 * @param desc une discription brève.
 */
void modifierRendezVous(T_RendezVous* *listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){

T_RendezVous *rdv = listeRdV;
  while (rdv != NULL && rdv->id_soi != idSoi){
    rdv = rdv->suivant;
  }
  rdv->debut_souhaitee = dateDebutSouhaitee;
  rdv->fin_souhaitee = dateFinSouhaitee;
  rdv->temps_deplacement = tempsDeplacement;
  rdv->desc = desc;
    
    //return provided_modifierRendezVous(listeRdV, idSoi, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement, desc);
}
/**
 * @brief Suppression d’un rendez-vous médical pour un patient en donnant l’identifiant du soigneur correspondant.
 * Si un rendez-vous, ni premier ni dernier, est enlevé, le temps de déplacement du traitement suivant doit être mis à jour.
 * Par exemple, un patient ayant trois rendez-vous : rendez-vous 1 chez le soigneur A,
 * rendez-vous 2 chez le soigneur B et rendez-vous 3 chez le soigneur C, temps de déplacement de 1 à 2 de 30 mn,
 * temps de déplacement de 2 à 3 de 40 mn, le temps de déplacement de 1 à 3 est défini
 * par sqrt(30^2+40^2)=50mn quand le rendez-vous 2 est supprimé.
 * @param listeRdV une liste de RdV.
 * @param idSoi identifiant d'un soigneur.
 * @return un pointeur vers la tête de la liste de RdV médicaux après une suppression.
 */
T_RendezVous* supprimerRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi){
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
                printf("Le rendez-vous n'existe pas  \n");
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
    
   // return provided_supprimerRendezVous(listeRdV, idSoi);


/**
 * @brief Afficher tous les soigneurs et leurs intervalles de temps disponibles
 * @param listeSoigneurs une liste de soigneurs.
 */
void affichage_Soigneurs(T_Soigneur* listeSoigneurs){
    T_Soigneur* SoigneurEnCours;
    //T_Intervalle* listeIntervallles=NULL;
    T_RendezVous* listeRdv=NULL;
    SoigneurEnCours = listeSoigneurs;
    while (SoigneurEnCours!=NULL)
    {
        printf("ID soigneur: %d\n",SoigneurEnCours->id_soi);
        printf("Nom: %s\n",SoigneurEnCours->nom);
        printf("Prenom: %s\n",SoigneurEnCours->prenom);
        //listeIntervallles=SoigneurEnCours->listeIntervalle;
        if(SoigneurEnCours->listeIntervalle!=NULL)
        {
            printf("Intervalle de temps disponible : [%d,%d[",SoigneurEnCours->listeIntervalle->debut,SoigneurEnCours->listeIntervalle->fin);

        }
        
/*         listeRdv = SoigneurEnCours->listeRendezVous;
 *         if (listeRdv!=NULL)
 *         {
 *             printf("Date de début affectée en minutes: %d\n ",listeRdv->debut_affectee);
 *             printf("Date de fin affectée en minutes: %d\n",listeRdv->fin_affectee);
 *             printf("ID soignant: %d\n",listeRdv->id_soi);
 *         }
 */
        SoigneurEnCours=SoigneurEnCours->suivant;
        printf("\n");
    }

}

/**
 * @brief Afficher tous les patients et leurs rendez-vous
 * @param listePatients une liste de patients.
 */
void affichage_Patients(T_Patient* listePatients){
    
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
 * @brief Afficher un rendez-vous en indiquant l’identifiant du patient et le soigneur correspondant
 * @param rendezVous un rendez-vous.
 */
void affichage_RendezVous(T_RendezVous rendezVous){
    if (rendezVous.id_soi==0){
        printf("Erreur: le rendez-vous demandé n'existe pas\n\n");
    } else {
        printf("Desc : %s\n",rendezVous.desc);
        printf("id_soigneur_associé : %d \n",rendezVous.id_soi);
        printf("temps_déplacement_depuis_rdv_précédent : %d \n",rendezVous.temps_deplacement);
        printf("RdV souhaité: [%d, %d[ \n",rendezVous.debut_souhaitee, rendezVous.fin_souhaitee);
        printf("RdV affecté: [%d, %d[ \n",rendezVous.debut_affectee,rendezVous.fin_affectee);
        printf("\n\n");
    }
}

void affichage_Tous_RendezVous(T_RendezVous *rendezVous){

    while (rendezVous!=NULL)
    {
        printf("Desc : %s\n",rendezVous->desc);
        printf("id_soigneur_associé : %d \n",rendezVous->id_soi);
        printf("temps_déplacement_depuis_rdv_précédent : %d \n",rendezVous->temps_deplacement);
        printf("RdV souhaité: [%d, %d[ \n",rendezVous->debut_souhaitee, rendezVous->fin_souhaitee);
        printf("RdV affecté: [%d, %d[ \n",rendezVous->debut_affectee,rendezVous->fin_affectee);
        rendezVous=rendezVous->suivant;
        printf("\n\n");
    }

}

/**
 * @brief Créer une instance de l’ordonnancement en important à partir d’un fichier.
 * @param filename le nom d'un fichier importé.
 * @return un pointeur vers l’instance.
 */
T_Ordonnancement* creerInstance(char* filename){

    T_Ordonnancement* monOrdonnancement;
    monOrdonnancement = malloc(sizeof(T_Ordonnancement));
    T_Patient* listePatientsO;
    listePatientsO=malloc(sizeof(T_Patient));
    T_Soigneur* listeSoigneursO;
    listeSoigneursO=malloc(sizeof(T_Soigneur));
    T_RendezVous* listeRendezVousO;
    listeRendezVousO = malloc(sizeof(T_RendezVous));
    FILE *fptxt;
    fptxt=fopen(filename,"r");
    int nbPatient =0;
    int nbSoignant = 0;
    int nbRdv =0;
    int idpat;
    int idsoigneur,interinf,intersup,tdepl;
    char nom[20],prenom[20], desc[100];
    if (fptxt==NULL)
    {
        printf("erreur lecture fichier");
    }
    else
    {
        printf("\n");
        fscanf(fptxt,"%d %d\n",&nbPatient,&nbSoignant);
        //printf("%d %d\n",nbPatient,nbSoignant);
        for (int i = 0; i < nbPatient; i++)
        {
            fscanf(fptxt,"%u %d %s %s\n",&idpat,&nbRdv,nom,prenom);
            //printf("%u %d %s %s\n",idpat,nbRdv,nom,prenom);
            printf("\n");
            ajouterPatient(&listePatientsO,idpat,nom,prenom);
            //printf("%u %d %s %s\n",idpat,nbRdv,nom,prenom);
            for (int j = 0; j < nbRdv; j++)
            {
                fscanf(fptxt,"%d %d %d %d %s\n",&idsoigneur,&interinf,&intersup,&tdepl,desc);
                //printf("%d %d %d %d %s\n",idsoigneur,interinf,intersup,tdepl,desc);
                //printf("\n");
                ajouterRendezVous(&listeRendezVousO,idsoigneur,interinf,intersup,tdepl,desc);
            }
            printf("\n");
        }
        printf("Récapitulatif Patients : \n\n");
        affichage_Patients(listePatientsO);
        for (int k = 0; k < nbSoignant; k++)
        {
            fscanf(fptxt,"%d %s %s\n",&idsoigneur,nom,prenom);
            //printf("%d %s %s\n",&idsoigneur,nom,prenom);
            ajouterSoigneur(&listeSoigneursO,idsoigneur,nom,prenom);
        }

        printf("\n");
        printf("Récapitulatif Soigneurs : \n\n");
        affichage_Soigneurs(listeSoigneursO);

        fclose(fptxt);
    }
    monOrdonnancement->listePatients=listePatientsO;
    monOrdonnancement->listeSoigneurs=listeSoigneursO;
    monOrdonnancement->listePatients->listeRendezVous=listeRendezVousO;

    return monOrdonnancement;
    //return provided_creerInstance(filename);
}

    /**
     * @brief Affectation d’un rendez-vous en fonction des intervalles de temps disponibles d’un soigneur
     * (mettre à jour la date de début affectée et la date de fin affectée du rendez-vous ) 
     * @param rdv un RdV.
     * @param soigneur un soigneur.
     */
    void affecterRdV(T_RendezVous* rdv, T_Soigneur* soigneur){
        return provided_affecterRdV(rdv, soigneur);
    }
    /**
     * @brief Ordonnancer les rendez-vous des patients en fonction des intervalles de temps disponibles
     * pour l’ensemble des soigneurs en minimisant la somme des temps d’attente des patients
     * (le temps d’attente est calculé par la date de début affectée – la date de début souhaitée).
     * L’algorithme glouton d'ordonnancement en minimisant la somme du temps d’attente des patients se construit comme suit :
     * Étape 1 : Trier les patients par ordre décroissant de durée totale des rendez-vous
 *  (la durée d’un rendez-vous est calculée par la date de fin souhaitée – la date de début souhaitée)
 * Étape 2 : Affecter les rendez-vous des patients dans l’ordre ci-dessus aux intervalles de temps disponible des soigneurs.
 * @param solution un instance
 */
void ordonnancer(T_Ordonnancement* solution){
    return provided_ordonnancer(solution);
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




/**
 * @brief un menu principal pour le programme.
 */
void menuPrincipal(void){


    T_Patient* listePatients;
    listePatients=malloc(sizeof(T_Patient));
    ajouterPatient(&listePatients,7, "Viera", "Baptiste");
    ajouterPatient(&listePatients,2, "Dupont", "Pierre");


    T_Soigneur* listeSoigneurs;
    listeSoigneurs=malloc(sizeof(T_Soigneur));
    ajouterSoigneur(&listeSoigneurs,7, "Legrand", "Jonathan");
    ajouterSoigneur(&listeSoigneurs,123, "Vincent", "Remi");

    T_Patient *patientExemple = chercher_Patient(listePatients);
    T_RendezVous **listeRendezVousExemple = &(patientExemple->listeRendezVous);
    ajouterRendezVous(listeRendezVousExemple,7,12,13,15,"Petit checkup du main");
    ajouterRendezVous(listeRendezVousExemple,8,34,33,16,"Visite");
    ajouterRendezVous(listeRendezVousExemple,9,45,56,17,"Visite");
    //modifierRendezVous(listeRendezVous,7,22,23,15,"Modification RDV");


    T_Ordonnancement* unOrdonnancement;
    
    char nomFichier[20];

    int choix;

    //Déclarations pour le case 4
    Index_Patient idPat;
    Index_Soigneur idSoi;
    T_Patient *patient;
    T_RendezVous rendezVousEnCours;
    T_RendezVous *listeRendezVous = NULL;
    //affichage_Tous_RendezVous(chercher_Patient(listePatients)->listeRendezVous);
    
    //Déclarations pour le case 5
    Time dateDebutSouhaitee;
    Time dateFinSouhaitee;
    Time tempsDeplacement;
    char desc[125];


    //printf("%s\n",chercher_Patient(listePatients)->nom); //Test de chercher_Patient

    do
    {

        /* affichage menu */
        printf("=================================================================================");
        printf("\nBienvenue au menu principal d'une application d'ordonnancement médical\n");
        printf("=================================================================================");

     printf("\n1: Créer une instance à partir d’un fichier\n"
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
            printf(" Veuillez saisir le nom du fichier d'une instance ");
            /*scanf("%s",nomFichier);
            if (!(strcmp(nomFichier,"instance1.txt"))&&(!strcmp(nomFichier,"instance2.txt")))
            {
                printf("Le fichier %s n'existe pas! Continuer? [y] n: ",nomFichier);
                exit(0);
            }*/
/*             unOrdonnancement = creerInstance("instance1.txt");
 *             T_Patient* listePatients = unOrdonnancement->listePatients;
 *             T_Soigneur* listeSoigneurs = unOrdonnancement->listeSoigneurs;
 */

            break;

         case 2:
            affichage_Patients(listePatients);
            break;

         case 3:
            affichage_Soigneurs(listeSoigneurs);
            break;

         case 4:            
            patient = chercher_Patient(listePatients);
            //printf("%s\n",patient->nom); //Test de chercher_Patient
            if (patient == NULL) {
                printf("Erreur: Aucun patient ne correspond à cet ID\n");
                break;
            }            
            affichage_Tous_RendezVous(patient->listeRendezVous);

            //On cherche dans la liste de rendez vous du patient le rdv correspondant au soigneur demandé
            printf("ID du soigneur?\n");
            scanf("%d",&idSoi);
            rendezVousEnCours = *(patient->listeRendezVous);
            while (rendezVousEnCours.suivant!=NULL){
                if (rendezVousEnCours.id_soi == idSoi){
                    break;
                }
                rendezVousEnCours = *rendezVousEnCours.suivant;
            }

            affichage_RendezVous(rendezVousEnCours);
            break;

         case 5:
            patient = chercher_Patient(listePatients);
            if (patient == NULL) {
                printf("Erreur: Aucun patient ne correspond à cet ID\n");
                break;
            }            
            affichage_Tous_RendezVous(patient->listeRendezVous);

            //On cherche dans la liste de rendez vous du patient le rdv correspondant au soigneur demandé
            printf("ID du soigneur?\n");
            scanf("%d",&idSoi);
            
            printf("Début souhaité?\n");
            scanf("%d",&dateDebutSouhaitee);
            
            printf("Fin souhaité?\n");
            scanf("%d",&dateFinSouhaitee);

            printf("Temps de déplacement nécessaire?\n");
            scanf("%d",&tempsDeplacement);
            
            printf("Description?\n");
            scanf("%s",&desc);


            modifierRendezVous(patient->listeRendezVous,idSoi,dateDebutSouhaitee,dateFinSouhaitee,tempsDeplacement,desc);
            affichage_Tous_RendezVous(patient->listeRendezVous);

            break;

         case 6:
            patient = chercher_Patient(listePatients);
            if (patient == NULL) {
                printf("Erreur: Aucun patient ne correspond à cet ID\n");
                break;
            }            
            affichage_Tous_RendezVous(patient->listeRendezVous);

            //On cherche dans la liste de rendez vous du patient le rdv correspondant au soigneur demandé
            printf("ID du soigneur?\n");
            scanf("%d",&idSoi);
            rendezVousEnCours = *supprimerRendezVous(patient->listeRendezVous,idSoi);
            affichage_Tous_RendezVous(patient->listeRendezVous);
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


    //return provided_menu();
}
