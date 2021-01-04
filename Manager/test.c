#include "headers.h"

// //TODO

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

void GAdminPerson (int choix)

{
    gotoxy(2,21);printf("Entrez le code Utilisateur ");
    gotoxy(2,22);printf(">>");
    int choice;
        choice = Choix2(1,9999,"Verifiez le format",5,22);
    switch(choix)
    {

    case 1:
        gotoxy(37,10);
        printf("1. Ajustement Salarial");
        gotoxy(37,12);
        printf("2. Ajustement du nombre de Credit");
        gotoxy(37,14);
        printf("3. Sortir");
        gotoxy(37,16);
        printf("Faites votre choix ");
        gotoxy(37,17);
        printf(">>");
        int choice;
        choice = Choix2(1,3,"Veuillez choisir entre 1 et 3",37+3,17);
        clearWindow();
        switch(choice)
        {
        case 1:
            gotoxy(37,10);
            printf("Entrez le nouveau salaire");
            gotoxy(37,11);
            printf(">>");
            // MoneyTester2(1);
            break;
        case 2:
            gotoxy(37,10);
            printf("Entrez le nombre de Credit");
            gotoxy(37,11);
            printf(">>");
            //int choi;
            // choi = Choix2(1,20,"Veuillez choisir entre 1 et 20",37+3,11);
            break;
        case 3:
            break;
        }

        break;
    case 2:
        gotoxy(37,10);
        printf("1. Ajustement de la Balance");
        gotoxy(37,12);
        printf("2. Ajustement de la date de paiement");
        gotoxy(37,14);
        printf("3. Sortir");
        gotoxy(37,16);
        printf("Faites votre choix ");
        gotoxy(37,17);
        printf(">>");
         choice = 0;
        choice = Choix2(1,3,"Veuillez choisir entre 1 et 3",37+3,17);
        clearWindow();
        switch(choice)
        {
        case 1:
            gotoxy(37,10);
            printf("Entrez la nouvelle Balance");
            gotoxy(37,11);
            printf(">>");
            // MoneyTester2(1);
            break;
        case 2:
            gotoxy(37,10);
            printf("Entrez la date de paiement");
            gotoxy(37,11);
            printf(">>");
            //int choi;
            // choi = Choix2(1,20,"Veuillez choisir entre 1 et 20",37+3,11);
            break;
        case 3:
            break;
        }

        break;
    case 3:
        gotoxy(37,10);
        printf("1. Ajustement Salarial");
        gotoxy(37,12);
        printf("2. Sortir");
        gotoxy(37,14);
        printf("Faites votre choix ");
        gotoxy(37,15);
        printf(">>");
         choice = 0;
        choice = Choix2(1,2,"Veuillez choisir entre 1 et 2",37+3,17);
        clearWindow();
        switch(choice)
        {
        case 1:
            gotoxy(37,10);
            printf("Entrez le nouveau Salaire");
            gotoxy(37,11);
            printf(">>");
            // MoneyTester2(1);
            break;

        case 2:
            break;
        }
        break;
    case 4:
        gotoxy(37,10);
        printf("1. Ajustement Cout");
        gotoxy(37,12);
        printf("2. Sortir");
        gotoxy(37,14);
        printf("Faites votre choix ");
        gotoxy(37,15);
        printf(">>");
        choice = 0;
        choice = Choix2(1,2,"Veuillez choisir entre 1 et 2",37+3,17);
        clearWindow();
        switch(choice)
        {
        case 1:
            gotoxy(37,10);
            printf("Entrez le nouveau Cout");
            gotoxy(37,11);
            printf(">>");












            // MoneyTester2(1);
            break;

        case 2:
            break;
        }

        break;

    }
    gotoxy(1,26);
    printf("Pressez 'Enter' pour retourner");
    getch();
    gotoxy(1,26);
    printf("                                 ");
    clearWindow();
}



void GCours(int choix)
{

    switch(choix)
    {

    case 1:
        PrintCours(0);
        break;
    case 2:
        PrintCours(1);
        break;
    case 3:
        AddCourse();
        gotoxy(1,26);
        printf("                                                                       ");
        clearWindow();
        break;
    case 4:

        break;

    }
    gotoxy(1,26);
    printf("Pressez 'Enter' pour retourner");
    getch();
    gotoxy(1,26);
    printf("                                 ");
    clearWindow();
}

int ChangePassword(int id)
{
    struct Utilisateur input;
    FILE *infile,*temp;

    infile = fopen ("Utilisateur.bin", "rb");
    temp = fopen ("Temp.bin", "ab");

    if (infile == NULL || temp == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    while(fread(&input,sizeof(struct Utilisateur), 1, infile))
    {
        if (id == input.Code)
        {
            gotoxy(1,26);
            printf("Entrez le nouveau mot de passe ");
            strcpy(input.Password,GetPassword()) ;
        }
        fwrite(&input,sizeof(struct Utilisateur), 1, temp) ;

    }

    fclose (infile);
    fclose(temp);
    remove("Utilisateur.bin");
    rename("Temp.bin","Utilisateur.bin");
    gotoxy(1,26);
    printf("                                                           ");
    gotoxy(1,26);
    printf("Succes!Pressez 'Entrer' pour continuer");
    // gotoxy(1,27);printf("Pressez 'Entrer' pour continuer");
    getch();
    gotoxy(1,26);
    printf("                                                   ");
    // gotoxy(1,27);printf("                                                   ");
    return 0;

}

int CheckUserAvailability (int id)
{
    FILE *infile;

    struct Utilisateur input;

    infile = fopen ("Utilisateur.bin", "rb");

    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    while(fread(&input,sizeof(struct Utilisateur), 1, infile))
    {


        if(id == input.Code)
        {
            fclose (infile);

            return id;
        }

    }

    fclose (infile);
    return 0;

}
