/****************************************************************
Author: Chenghao WANG
Contact: chenghao.wang@hds.utc.fr
Institute: Heudiasyc, université de technologie de compiègne
Date: 12/10/2020
*****************************************************************/
#include "../include/TP3.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ajouterIntervalle
 *  Description:  
 * =====================================================================================
 */
T_Intervalle* ajouterIntervalle ( T_Intervalle** listeIntervalle, Time debut, Time fin )
{
    if(*listeIntervalle == NULL){
        printf("Erreur: la liste d'intervalles disponibles est nulle");
        exit(EXIT_FAILURE);
    }
    T_Intervalle *intervalle = malloc(sizeof(T_Intervalle));
    intervalle->debut = debut;
    intervalle->fin = fin;

    intervalle->suivant = *listeIntervalle;
    *listeIntervalle = intervalle;
    printf("L'intervalle a bien été ajouté\n");
    return intervalle;
}		/* -----  end of function ajouterIntervalle  ----- */



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  supprimerIntervalle
 *  Description:  
 * =====================================================================================
 */
void supprimerIntervalle (T_Intervalle** listeIntervalle,T_Intervalle* intervalle )
{
    printf("Moi ça va je supprime des intervalles\n");
    T_Intervalle* intervalleActuel = *listeIntervalle;

    if(*listeIntervalle == NULL){
        printf("Erreur dans supprimerIntervalle: la liste d'intervalles disponibles est nulle ou l'intervalle à supprimer n'existe pas");
        exit(EXIT_FAILURE);
    }

    while(intervalleActuel->suivant != NULL){
        if(intervalleActuel->suivant == intervalle ){
            intervalleActuel->suivant = intervalle->suivant;
            free(intervalle);
            printf("L'intervalle a été supprimé\n");
            break;
        }
    }

}		/* -----  end of function supprimerIntervalle  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  chercher_RdV
 *  Description:  
 * =====================================================================================
 */
T_RendezVous* chercher_RdV ( T_RendezVous *listeRendezVous, Index_Soigneur idSoi )
{
    T_RendezVous *rendezVousEnCours = listeRendezVous;
    while (rendezVousEnCours!=NULL){
        if (rendezVousEnCours->id_soi == idSoi){
            return rendezVousEnCours;
        }
        rendezVousEnCours = rendezVousEnCours->suivant;
    }
    return NULL;
}		/* -----  end of function chercher_RdV  ----- */



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
        soigneur->listeIntervalle->fin=32700; // 24h


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
                //rdvpred->suivant=rdvsucc->suivant;
                /*Time newTempsDeplacement;
                T_RendezVous* temp=rdvsucc->suivant;
                printf("COucou");
                if (rdvsucc->suivant!=NULL)
                {
                    //temp = rdvsucc->suivant;
                    printf("COucou");
                    newTempsDeplacement = sqrt(pow(rdvsucc->temps_deplacement,2)+pow(rdvsucc->suivant->temps_deplacement,2));
                    printf("\nNew Temps : %d\n",newTempsDeplacement);
                    temp = rdvsucc->suivant;
                    modifierRendezVous(&temp,temp->id_soi,temp->debut_souhaitee,temp->fin_affectee,newTempsDeplacement,temp->desc);
                    //rdvpred->suivant=temp;
                }
                rdvpred->suivant=temp;
                free(rdvsucc);*/

                Time newTempsDeplacement;
                //T_RendezVous* temp;
                //printf("COucou");
                if (rdvsucc->suivant!=NULL)
                {
                    //temp = rdvsucc->suivant;
                    //printf("COucou");
                    newTempsDeplacement = sqrt(pow(rdvpred->temps_deplacement,2)+pow(rdvpred->suivant->temps_deplacement,2));
                    //printf("\nNew Temps : %d\n",newTempsDeplacement);
                    //temp = rdvpred;
                    //printf("\nId : %d\n",rdvpred->id_soi);
                    //printf("\nCoucou\n");
                    //printf("\Temps : %d\n",rdvpred->temps_deplacement);
                    modifierRendezVous(rdvpred,rdvpred->id_soi,rdvpred->debut_souhaitee,rdvpred->fin_souhaitee,newTempsDeplacement,rdvpred->desc);
                    //rdvpred->suivant=temp;
                }
                rdvpred->suivant=rdvsucc->suivant;
                printf("\n\nLe temps de déplacements du rendez-vous suivant associé à l'ID soignant %d a été mise à jour. Voir ci-dessous \n\n", rdvpred->id_soi);
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
    T_Intervalle *intervalleActuel = NULL;
    while (SoigneurEnCours->suivant!=NULL)
    {
        printf("ID soigneur: %d\n",SoigneurEnCours->id_soi);
        printf("Nom: %s\n",SoigneurEnCours->nom);
        printf("Prenom: %s\n",SoigneurEnCours->prenom);
        //listeIntervallles=SoigneurEnCours->listeIntervalle;
        printf("Intervalles de temps disponible : \n"); 
        intervalleActuel = SoigneurEnCours->listeIntervalle;
        while(intervalleActuel != NULL)
        {
            printf("[%d,%d]",intervalleActuel->debut,intervalleActuel->fin);
            intervalleActuel = intervalleActuel->suivant;
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
        printf("\n\n");
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
   while (PatientEnCours->suivant!=NULL)
   {
       printf("ID patient: %d\n",PatientEnCours->id_pat);
       printf("Nom: %s\n",PatientEnCours->nom);
       printf("Prenom: %s\n",PatientEnCours->prenom);
       listeRdv = PatientEnCours->listeRendezVous;
       if (listeRdv!=NULL)
       {
           printf("Date de début affectée en minutes: %d\n",listeRdv->debut_affectee);
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

    while (rendezVous->suivant!=NULL)
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

    listePatientsO->listeRendezVous=listeRendezVousO;

    FILE *fptxt;
    fptxt=fopen(filename,"r");
    int nbPatient =0, nbSoignant = 0, nbRdv =0;
    int idpat, idsoigneur,interinf,intersup,tdepl;
    char *nom,*prenom, *desc;
    desc=malloc(sizeof(0));
    nom=malloc(sizeof(0));
    prenom=malloc(sizeof(0));

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
            fscanf(fptxt,"%d %d %s %s\n",&idpat,&nbRdv,nom,prenom);
            //printf("%u %d %s %s\n",idpat,nbRdv,nom,prenom);
            printf("\n");
            ajouterPatient(&listePatientsO,idpat,nom,prenom);
            
            for (int j = 0; j < nbRdv; j++)
            {
                fscanf(fptxt,"%d %d %d %d %s\n",&idsoigneur,&interinf,&intersup,&tdepl,desc);
                //printf("%d %d %d %d %s\n",idsoigneur,interinf,intersup,tdepl,desc);
                //printf("\n");
                ajouterRendezVous(&(listePatientsO->listeRendezVous),idsoigneur,interinf,intersup,tdepl,desc);
                desc=malloc(0);
            }

            printf("\n");

            nom=malloc(0); // cela permet en quelque sorte de libérer la mémoire pour l'itération suivante
            prenom=malloc(0); 
        }

        printf("Récapitulatif Patients : \n\n");
        affichage_Patients(listePatientsO);
        
        for (int k = 0; k < nbSoignant; k++)
        {
            
            fscanf(fptxt,"%d %s %s\n",&idsoigneur,nom,prenom);
            printf("\n");
            //printf("%d %s %s\n",&idsoigneur,nom,prenom);
            ajouterSoigneur(&listeSoigneursO,idsoigneur,nom,prenom);
            nom=malloc(0);
            prenom=malloc(0);
        }

        printf("\n");
        printf("Récapitulatif Soigneurs : \n\n");
        affichage_Soigneurs(listeSoigneursO);

        fclose(fptxt);
    }
 
    monOrdonnancement->listePatients=listePatientsO;
    monOrdonnancement->listeSoigneurs=listeSoigneursO;


    char *today; 
    time_t timestamp = time(NULL); 
    today=malloc(sizeof(0));
  
    strftime(today,100, "%Y-%m-%d", localtime(&timestamp));
    monOrdonnancement->date=today;
    printf("Date de creation de l'ordonnancement : %s\n\n",today);
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
    printf("Soigneur %s:\n",soigneur->prenom);
    Time debutI, finI, debut_affectee = 0, fin_affectee = 0;

    T_Intervalle* intervalle; 
    intervalle = soigneur->listeIntervalle;
    //On cherche un intervalle de temps disponible qui correspond à l'intervalle souhaité
    do{
        debutI = intervalle->debut;
        finI = intervalle->fin;
        if(rdv->debut_souhaitee >= debutI && rdv->fin_souhaitee <= finI){
            printf("Le soigneur est disponible à l'intervalle demandé \n");
            debut_affectee = rdv->debut_souhaitee;
            fin_affectee = rdv->fin_souhaitee;
            break;
        }
    }while(intervalle->suivant != NULL);

    //Si aucun intervalle ne permet d'avoir un rdv au moment souhaité, on affecte un rendez vous après le dernier rdv du soigneur
    if (debut_affectee == 0 && fin_affectee == 0){
        printf("Aucun intervalle libre au moment souhaité. On affecte au dernier intervalle du soigneur \n");
        debut_affectee = intervalle->debut; 
        fin_affectee = debut_affectee + rdv->fin_souhaitee - rdv->debut_souhaitee; 
    }

    //Modification de la liste d'intervalles de temps disponible du soigneur en fonction du rdv affecté
    if (debutI == debut_affectee ){
        if(finI == fin_affectee){
            printf("Le rdv souhaité correspond parfaitement à un intervalle libre du soigneur, on supprime [%d,%d]\n",debutI,finI);
            supprimerIntervalle(&(soigneur->listeIntervalle),intervalle);
        } else {
            intervalle->debut = fin_affectee;
            printf("Le rdv souhaité colle au début d'un intervalle libre du soigneur, on transforme [%d,%d] en [%d,%d]",debutI,finI,fin_affectee,finI);

        }
    } else {
        if(finI == fin_affectee){ //cas finI colle, debutI ne colle pas
            intervalle->fin = debut_affectee;
        } else {
            printf("Cas milieu d'un intervalle disponible, on transforme [%d,%d] en [%d,%d] et on ajoute [%d,%d]\n",debutI,finI,debutI,debut_affectee,fin_affectee,finI);
            intervalle->fin = debut_affectee;
            ajouterIntervalle(&(soigneur->listeIntervalle),fin_affectee,finI);
        }
    }

    //On modifie le rdv pour montrer qu'il a été affecté à un soigneur
    rdv->debut_affectee = debut_affectee;
    rdv->fin_affectee = fin_affectee;
    //rdv->id_soi = soigneur->id_soi;


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

    /*T_Patient* listePatients = solution->listePatients;
    while (listePatients!=NULL)
    {
        printf("%d\n\n",provided_sommeDeDurationRendezVous(listePatients));
        listePatients = listePatients->suivant;

    }*/
    
    //provided_MergeSort(&(solution->listePatients));
    return provided_ordonnancer(solution);


}
/**
 * @brief Exporter la solution d’un ordonnancement.
 * Le nom du fichier exporté a sufix de la date de création  d’un ordonnancement, par exemple filename=’solution.txt’,
 * et la date de creation est ‘2020-10-13’, donc le nom de ficher exporté est ‘solution.txt.2020-10-13.txt’.
 * @param solution une solution d'un ordonnancement.
 * @param filename le nom d'un ficher exporté.
 */


void ExportSolution(T_Ordonnancement* solution, char* filename)
    {

    T_Patient* listePat = solution->listePatients;
    T_Soigneur* listeSoig = solution->listeSoigneurs;
    //T_RendezVous* listeRdV = solution->listePatients->listeRendezVous;


    int nbPat=0, nbSoig = 0, nbRdV = 0;
    
    FILE *fptxt;
    int i =0;
    char finalfilename[1024];
    char point[] =".";
    char ext [] =".txt";

    /*strcat(finalfilename,filename);
    printf("%s\n\n",finalfilename);
    strcat(finalfilename,point);
    printf("%s\n\n",finalfilename);    
    strcat(finalfilename,solution->date);
    printf("%s\n\n",finalfilename);
    strcat(finalfilename,ext);*/

    snprintf( finalfilename, sizeof( finalfilename ), "%s%s%s%s", filename,point,solution->date, ext);

    fptxt=fopen(finalfilename,"w");

    if (fptxt==NULL) // test d'erreur
    {
        printf("erreur ecriture fichier");
    }
        
    while (listePat->suivant!=NULL)
    {
        nbPat++;
        listePat=listePat->suivant;
    }
    //printf("%d\n\n",nbPat);

    while (listeSoig->suivant!=NULL)
    {
        nbSoig++;
        listeSoig=listeSoig->suivant;

    }

    /*while (listeRdV!=NULL)
    {
        nbRdV++;
        listeRdV=listeRdV->suivant;

    }*/

    listePat = solution->listePatients;
    listeSoig = solution->listeSoigneurs;
    listePat->listeRendezVous=solution->listePatients->listeRendezVous;
    //printf("%d\n\n",listePat->listeRendezVous->id_soi);
    //listeRdV = solution->listePatients->listeRendezVous;
    T_RendezVous* debutRDV=NULL;

    // pas besoin de retourner au début car les premier élément insérer à partir du fichier se trouve a la fin des listes

    fprintf(fptxt,"%d %d\n",nbPat,nbSoig);
    for (int i = 0; i < nbPat; i++)
    {   
        //debutRDV = listePat->listeRendezVous;
       /*while (listePat->listeRendezVous->suivant!=NULL)
        {
            nbRdV++;
            listePat->listeRendezVous=listePat->listeRendezVous->suivant;
        }*/
        //printf("%d\n\n",nbRdV);
        //listePat->listeRendezVous=debutRDV;

        nbRdV = provided_compter_nb_Rdv_par_patient(listePat->id_pat,listePat);
        //printf("%d\n\n",nbRdV);
        nbRdV--;
        fprintf(fptxt,"%d %d\n",listePat->id_pat,nbRdV);
        for (int j = 0; j < nbRdV; j++)
        {
            fprintf(fptxt,"%d %d %d %d\n",listePat->listeRendezVous->id_soi,listePat->listeRendezVous->debut_affectee,listePat->listeRendezVous->fin_affectee,listePat->listeRendezVous->temps_deplacement);
            listePat->listeRendezVous=listePat->listeRendezVous->suivant;
        }
        listePat=listePat->suivant;

    }
    

    fclose(fptxt);

    printf("\nLa solution a bien été exportée\n");

}
    
    //return provided_exportSolution(solution, filename);





/**
 * @brief un menu principal pour le programme.
 */
void menuPrincipal(void){


    T_Patient* listePatients;
/*     listePatients=malloc(sizeof(T_Patient));
 *     ajouterPatient(&listePatients,7, "Viera", "Baptiste");
 *     ajouterPatient(&listePatients,2, "Dupont", "Pierre");
 * 
 */

    T_Soigneur* listeSoigneurs;
/*     listeSoigneurs=malloc(sizeof(T_Soigneur));
 *     ajouterSoigneur(&listeSoigneurs,7, "Legrand", "Jonathan");
 *     ajouterSoigneur(&listeSoigneurs,123, "Vincent", "Remi");
 */

    /*T_Patient *patientExemple = chercher_Patient(listePatients);
    T_RendezVous **listeRendezVousExemple = &(patientExemple->listeRendezVous);
    ajouterRendezVous(listeRendezVousExemple,7,12,13,15,"Petit checkup du main");
    ajouterRendezVous(listeRendezVousExemple,8,34,33,16,"Visite");
    ajouterRendezVous(listeRendezVousExemple,9,45,56,17,"Visite");*/

    //modifierRendezVous(listeRendezVous,7,22,23,15,"Modification RDV");


    T_Ordonnancement* unOrdonnancement;
    
    char nomFichier[20];

    int choix;
    char *rep;
    rep=malloc(sizeof(0));
    int OK1 = 0;
    int OK2 = 0;

    //Déclarations pour le case 4
    Index_Patient idPat;
    Index_Soigneur idSoi;
    T_Patient *patient;
    T_RendezVous *rendezVous;
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
             "9: Affecter rendez-vous (test)\n"
             "10: Quitter\n");
 
      fflush(stdin);
      printf("\nVotre choix ? ");
      scanf("%d",&choix);
 
      switch(choix)
      {
         case 1:
            do
        {
            printf("\nVeuillez saisir le nom du fichier d'une instance : ");
            fflush(stdin);
             scanf("%s",nomFichier);
           if ((strcmp(nomFichier,"instance1.txt"))&&(strcmp(nomFichier,"instance2.txt")))
             {
                
                printf("Le fichier %s n'existe pas!\n",nomFichier);
                printf("Voulez-vous continuer ? (oui ou non) : ");
                fflush(stdin);
                scanf("%s",rep);
                if (!strcmp(rep,"non"))
                {
                    OK2=1;
                }
                rep=malloc(0);

                
                
            }
            else
            {
                OK1=1;
            }
            
        } while (OK1==0 && OK2==0);
               
           
            if (OK1)
            {
            unOrdonnancement = creerInstance(nomFichier);
            T_Patient* listePatients = unOrdonnancement->listePatients;
            T_Soigneur* listeSoigneurs = unOrdonnancement->listeSoigneurs;
            }
            OK1=0;
            OK2=0;
              
            break;

         case 2:
            affichage_Patients(unOrdonnancement->listePatients);
            break;

         case 3:
            affichage_Soigneurs(unOrdonnancement->listeSoigneurs);
            break;

         case 4:            
            patient = chercher_Patient(unOrdonnancement->listePatients);
            //printf("%s\n",patient->nom); //Test de chercher_Patient
            if (patient == NULL) {
                printf("Erreur: Aucun patient ne correspond à cet ID\n");
                break;
            }            
            affichage_Tous_RendezVous(patient->listeRendezVous);

            //On cherche dans la liste de rendez vous du patient le rdv correspondant au soigneur demandé
            printf("ID du soigneur?\n");
            scanf("%d",&idSoi);

            rendezVous = chercher_RdV(patient->listeRendezVous,idSoi);
            if (rendezVous == NULL) {
                printf("Erreur: Le patient n'a pas de rendez vous avec le soigneur %d ou le soigneur %d n'existe pas\n",idSoi,idSoi);
                break;
            }       
            affichage_RendezVous(*rendezVous);
            break;

         case 5:
            patient = chercher_Patient(unOrdonnancement->listePatients);
            if (patient == NULL) {
                printf("Erreur: Aucun patient ne correspond à cet ID\n");
                break;
            }            
            affichage_Tous_RendezVous(patient->listeRendezVous);

            printf("ID du soigneur?\n");
            scanf("%d",&idSoi);
            
            printf("Début souhaité?\n");
            scanf("%d",&dateDebutSouhaitee);
            
            printf("Fin souhaité?\n");
            scanf("%d",&dateFinSouhaitee);

            printf("Temps de déplacement nécessaire?\n");
            scanf("%d",&tempsDeplacement);
            
            printf("Description?\n");
            scanf("%s",desc);


            modifierRendezVous(patient->listeRendezVous,idSoi,dateDebutSouhaitee,dateFinSouhaitee,tempsDeplacement,desc);
            affichage_Tous_RendezVous(patient->listeRendezVous);

            break;

         case 6:
            patient = chercher_Patient(unOrdonnancement->listePatients);
            if (patient == NULL) {
                printf("Erreur: Aucun patient ne correspond à cet ID\n");
                break;
            }            
            affichage_Tous_RendezVous(patient->listeRendezVous);

            //On cherche dans la liste de rendez vous du patient le rdv correspondant au soigneur demandé
            printf("ID du soigneur?\n");
            scanf("%d",&idSoi);
            patient->listeRendezVous = supprimerRendezVous(patient->listeRendezVous,idSoi);
            affichage_Tous_RendezVous(patient->listeRendezVous);
            break;

         case 7:
            //ordonnancer(unOrdonnancement); 
            //Test de affecterRdV

            //rendezVousEnCours = chercher_RdV(patientExemple->listeRendezVous,7);
            //affecterRdV(rendezVous,listeSoigneurs);*
            //ajouterIntervalle(&(listeSoigneurs->listeIntervalle),100,200);
            //affecterRdV(rendezVous,listeSoigneurs);

            break;

         case 8:
            ExportSolution(unOrdonnancement, "solution.txt");
            break;
        
        case 9:
            affecterRdV(rendezVous,unOrdonnancement->listeSoigneurs);
            break;        

        case 10:
            break;

        default:
            printf("Choix erroné\n");
      }
   }while(choix!=10);


    //return provided_menu();
}


//Ne pas oublier :
//Arrêter d'afficher les éléments nuls dans les listes
//Les rdv sont bizarres dans afficher patients
//Vérifier si les listes existent pour éviter les segmentation fault si aucune instance n'est chargée




