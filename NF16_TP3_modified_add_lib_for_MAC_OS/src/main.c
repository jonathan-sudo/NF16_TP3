#include <stdio.h>
#include "../include/TP3.h"
#include <stdlib.h>



int main() {
    T_Patient *listePatients;
    listePatients = malloc(sizeof(listePatients));
    ajouterPatient(listePatients,1,"Viera","Baptiste");
    ajouterPatient(listePatients,2,"Kowalski","Jan");

    T_Soigneur *listeSoigneurs;
    listeSoigneurs = malloc(sizeof(listeSoigneurs));
    ajouterSoigneur(listeSoigneurs,2,"Legrand","Jonathan");
    ajouterSoigneur(listeSoigneurs,3,"Vincent","Rémi");
    
    T_RendezVous *listeRendezVous;
    listeRendezVous = malloc(sizeof(listeRendezVous));
    ajouterRendezVous(listeRendezVous,1,10,11,2,"Rdv test avec Jonathan");
    ajouterRendezVous(listeRendezVous,1,10,11,3,"Rdv test avec Rémi");



    menuPrincipal();
    return 0;
}



