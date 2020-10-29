#include <stdio.h>
#include "../include/TP3.h"
#include <stdlib.h>



int main() {
    T_Patient *listePatients;
    listePatients = malloc(sizeof(listePatients));
    ajouterPatient(listePatients,1,"Viera","Baptiste");
    ajouterPatient(listePatients,1,"Kowalski","Jan");

    T_Patient *listeSoigneurs;
    listeSoigneurs = malloc(sizeof(listeSoigneurs));
    ajouterPatient(listeSoigneurs,1,"Viera","Baptiste");
    ajouterPatient(listeSoigneurs,1,"Kowalski","Jan");

    menuPrincipal();
    return 0;
}



