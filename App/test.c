#include "headers.h"

// //TODO 
// Changer password
// hide password
// modifier user
int MenuPrincipal (int code)
{
    printf("1. Menu 01 : Gestion des accès\n");
    printf("2. Menu 02 : Cours\n");
    printf("3. Menu 03 : Administration et comptabilité\n");
    printf("4. Menu 04 : Bibliothèque\n");
    printf("5. Menu 05 : Quitter le programme\n");
}
int MenuGestionAccess(int code)//?????
{
    printf("1. Menu 01 : Lister les Administrateurs\n");
    printf("2. Menu 02 : Lister les Etudiants\n");
    printf("3. Menu 03 : Lister les Agents AdministratifS\n");
    printf("4. Menu 04 : Lister les Bibliothécaires\n");
    printf("5. Menu 05 : Modifier un mot de passe\n"); 
    printf("6. Menu 06 : Sortir\n"); 

}

int MenuCours(int code)
{
    printf("1. Menu 01 : Afficher les cours\n");
    printf("2. Menu 02 : Afficher les informations sur un cours\n");
    printf("3. Menu 03 : Ajouter un cours\n");
    printf("4. Menu 04 : Modifier un cours\n");
    printf("5. Menu 05 : Sortir\n"); 

}

int MenuOuvrage(int code)
{
    printf("1. Menu 01 : Afficher les catégories\n");
    printf("2. Menu 02 : Afficher les ouvrages\n");
    printf("3. Menu 03 : Ajouter un ouvrage\n");
    printf("4. Menu 04 : Emprunter un ouvrage\n");
    printf("5. Menu 05 : Retourner un ouvrage\n"); 
    printf("6. Menu 06 : Sortir\n"); 

}

int MenuAdmComp(int code)
{
    printf("1. Menu 01 : Gestion des professeurs\n");
    printf("2. Menu 02 : Gestion des étudiants\n");
    printf("3. Menu 03 : Gestion du personnel administratif\n");
    printf("4. Menu 04 : Modifier un cours\n");
    printf("5. Menu 05 : Sortir\n"); 

}
int SubMenuAdmProf(int code)
{
    printf("1. Menu 01 : Ajustement Salarial\n");
    printf("2. Menu 02 : Ajustement du nombre de Credit\n");
    printf("3. Menu 03 : Sortir\n"); 

}

int SubMenuAdmStud(int code)
{
    printf("1. Menu 01 : Ajustement de la Balance\n");
    printf("2. Menu 02 : Ajustement de la date de paiement\n");
    printf("3. Menu 03 : Sortir\n"); 

}

int SubMenuAdmPers(int code)
{
    printf("1. Menu 01 : Ajustement Salarial\n");
    printf("2. Menu 02 : Sortir\n"); 
}

int SubMenuAdmCours(int code)
{
    printf("1. Menu 01 : Ajustement du cout\n");
    printf("2. Menu 02 : Sortir\n"); 
}
