#include "headers.h"
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);

}

typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

int isValidDate(Date *validDate)
{
    //check range of year,month and day
    time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    int MIN_YR = current_time->tm_year + 1900;

    if (validDate->yyyy > 2030 ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
char *GetDate()
{
    Date getDate = {0}; //variable to store date
    int status = 0; //variable to check status
    static char date[50];

    //get date year,month and day from user
    scanf("%d/%d/%d",&getDate.dd,&getDate.mm,&getDate.yyyy);
    //check date validity
    status = isValidDate(&getDate);
    if(status !=1)
    {
        printf("Veuillez entrer une date valide!\n");
        clean_stdin();
        GetDate();
    }
    else
    {
        sprintf(date,"%d/%d/%d",getDate.dd,getDate.mm,getDate.yyyy);
	    return date;
    }

}

char * GetNIF()
 {
    int d1, d2, d3,d4;
    int val;
    static char NIF[20];
    printf("Entrez le NIF en format :xxx-xxx-xxx-x: ");
    val = scanf("%d-%d-%d-%d", &d1, &d2, &d3 , &d4);
    // check if scanf was successful
    if(val == 4)
    {
     sprintf(NIF,"%d-%d-%d-%d",d1,d2,d3,d4);
	  return NIF;
    }
    clean_stdin();
    printf("\nFormat de NIF invalid, veuillez reesayer!\n");
    GetNIF();

}

int GetLastID(int fileCode)
{
    int id;
    FILE *infile;
	char file[20];

	struct Utilisateur input;
	char fichier1[] = "Utilisateur.bin";
	int size1 = sizeof(struct Utilisateur);

    struct Cours input2;
    char fichier2[] = "Cours.bin";
    int size2 = sizeof(struct Cours);

	if (fileCode == 1)
	{
		infile = fopen (fichier1, "rb");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input,size1, 1, infile))
		id = input.Code;

	}
    else if (fileCode == 2)
	{
		infile = fopen (fichier2, "rb");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input2,size2, 1, infile))
		id = input2.Code;

	}


	fclose (infile);
	return id;
}

char *GetString()
{
    static char text[100];
    fflush(stdin);
    //printf(">>");
    //clean_stdin();
     if (fgets(text, 100, stdin) == NULL)
     {
      printf("Ce champ est obligatoire .");
	  clean_stdin();
      GetString();
     }
     strtok(text, "\n");
     return text;

}

int GetAccess (  )

{
	FILE *infile;
	struct Utilisateur input;

	char code[100];
	int user,id, val ;
    clearWindow();

        print_heading("Connection");
        gotoxy(37,10);printf("Code Utilisateur  : ");
        val = scanf("%d",&id);

        gotoxy(37,12);printf("Mot de Passe      : ");

        strcpy(code,GetPassword());
        if (val == 0)
        {
            gotoxy(37,14);printf("ID ou mot de Passe incorrect");
            gotoxy(37,16);printf("Pressez 'Enter' pour reesayer");
            getch();
            GetAccess();
            return 0;
        }



	infile = fopen ("Utilisateur.bin", "rb");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input,sizeof(struct Utilisateur), 1, infile))
	{

		if (id ==input.Code )
		{
			if (strcmp(code, input.Password)== 0)
			{
                clearWindow();
				return id;
			}
		}

	}
	gotoxy(37,14);printf("ID ou mot de Passe incorrect");
            gotoxy(37,16);printf("Pressez 'Enter' pour reesayer");
            getch();
	 GetAccess();
		return 0;
}

char *Today ()
{
	time_t t ;
	struct tm *tmp ;
	static char MY_TIME[50];
	time( &t );


	tmp = localtime( &t );
	strftime(MY_TIME, sizeof(MY_TIME), "%x - %I:%M%p", tmp);

	return MY_TIME;
}

int Choix(int min,int max , char *warning)
{
  char term;
  int input;
  fflush(stdin);
    //clean_stdin();
  if (scanf("%d%c", &input, &term) == 2 && term == '\n'&& input>=min && input <= max)
   {
     return input;
   }
  else
   {
    printf("%s",warning);
     Choix(min,max,warning);
   }
}

int AddUser ()
{
struct Utilisateur NewUser;
int test;

NewUser.Code = GetLastID(1)+1;
strcpy(NewUser.NIF,GetNIF());
clean_stdin();
printf("Entrez le Nom : ");
strcpy(NewUser.Nom,GetString());
printf("Entrez le Prenom : ");
strcpy(NewUser.Prenom,GetString());
printf("Entrez le Mot de Passe : ");
strcpy(NewUser.Password,GetString());
strcpy(NewUser.Date,Today());

printf("Choisissez une categorie. \n");
printf("0 : Administrateur\n1 : Etudiant(e)\n2 : Professeur\n3 : Agent administratif\n4 : Bibliothecaire\n");

test=Choix(0,4,"Veuillez choisir par la liste!");
NewUser.Module =test;

if (test== 0)
   strcpy(NewUser.Type, "Administrateur");
   else
   strcpy(NewUser.Type, "Utilisateur");

switch ((test))
   {
   case 0:
       strcpy(NewUser.Categorie, "Administrateur");
       break;
   case 1:
       strcpy(NewUser.Categorie, "Etudiant(e)");
	   AddStudent(NewUser.Code,NewUser.Nom,NewUser.Prenom);
       break;
   case 2:
       strcpy(NewUser.Categorie, "Professeur");
	   AddTeacher(NewUser.Code,NewUser.Nom,NewUser.Prenom);
       break;
    case 3:
       strcpy(NewUser.Categorie, "Agent Administratif");
       AddPersonnel (NewUser.Code,NewUser.Nom,NewUser.Prenom);
       break;
    case 4:
       strcpy(NewUser.Categorie, "Bibliothecaire");
       AddBibliothecaire (NewUser.Code);
       break;
   }


// printf("New User infos: \n");
//  printf("Code :%d\n",NewUser.Code);
//         printf("Nom :%s\n",NewUser.Nom);
//         printf("Prenom :%s\n",NewUser.Prenom);
//         printf("NIF-CIN :%s\n",NewUser.NIF);
//         printf("Type:%s\n",NewUser.Type);
//         printf("Categorie :%s\n",NewUser.Categorie);
//         printf("Module : %d\n",NewUser.Module);


FILE *outfile;

	// open file for writing
	outfile = fopen ("Utilisateur.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewUser, sizeof(struct Utilisateur), 1, outfile);

	if(fwrite != 0)
		printf("Votre utilisateur a ete enregistre avec succes. Code : %d\n",NewUser.Code);
	else
		printf("Erreurs lors de l'enregistrement.\n");

	// close file
	fclose (outfile);



return 1;
}

int AddStudent (int id , char *nom ,char *prenom )
{
    struct Student NewUser;
    int test ,test2 ,cur ;
     time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    cur = current_time->tm_year + 1900;
    // printf("Current year = %d\n",(current_time->tm_year + 1900));

    NewUser.Code = id;
    printf("Veullez entrer la session (max 20) \n");
    NewUser.Session=Choix(1,20,"Veuillez choisir un nombre entre 1 et 20!\n");
    printf("Veuillez entrer l'annee d'admission\n");
    NewUser.AnneeAdm=Choix(1988,cur,"Veuillez entrer une annee entre 1988 et l'annee actuelle!");

    printf("Choisissez une Faculte. \n");
    printf("0 : Faculté des Sciences Économiques et Administratives (FSEA)\n1 : Faculté des Sciences, de Génie et d'Architecture (FSGA)\n2 : Faculté des Sciences de l’Agriculture et de l’Environnement (FSAE)\n3 : Faculté des Sciences Juridiques et Politiques (FSJP)\n4 : Faculté des Sciences de l'Education (FSED)\n5 : Faculté des Sciences de la Santé (FSSA)\n");
    test=Choix(0,5,"Veuillez choisir par la liste!");

switch ((test))
   {
   case 0:
       strcpy(NewUser.Faculte, "FSEA");
       printf("Choisissez une Section. \n");
       printf("0 : Gestion des Ressources humaines\n1 : Gestion des Affaires\n2 :Comptabilité de Management \n3 : Micro finance\n4 : Gestion de Projet\n5 :Marketing \n6 : Sciences économiques\n7 : Sciences administratives-PME\n8 : Sciences administratives-Sciences comptables\n9 : Sciences administratives-Gestion touristique\n10 : Sciences administratives-Gestion des institutions financières\n");
        printf("11 : Sciences administratives-Finance\n12 : Maîtrise en comptabilité:Contrôle-Audit\n13 : Maîtrise en gestion de projet\n");
       test2=Choix(0,13,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Gestion des Ressources humaines");
            break;
        case 1:
            strcpy(NewUser.Section, "Gestion des Affaires");
            break;
        case 2:
            strcpy(NewUser.Section, "Comptabilité de Management");
            break;
        case 3:
            strcpy(NewUser.Section, "Micro finance");
            break;
        case 4:
            strcpy(NewUser.Section, "Gestion de Projet");
            break;
        case 5:
            strcpy(NewUser.Section, "Marketing");
            break;
        case 6:
            strcpy(NewUser.Section, "Sciences économiques");
            break;
        case 7:
            strcpy(NewUser.Section, "Sciences administratives-PME");
            break;
        case 8:
            strcpy(NewUser.Section, "Sciences administratives-Sciences comptables");
            break;
        case 9:
            strcpy(NewUser.Section, "Sciences administratives-Gestion touristique");
            break;
        case 10:
            strcpy(NewUser.Section, "Sciences administratives-Gestion des institutions financières");
            break;
        case 11:
            strcpy(NewUser.Section, "Sciences administratives-Finance");
            break;
        case 12:
            strcpy(NewUser.Section, "Maîtrise en comptabilité:Contrôle-Audit");
            break;
        case 13:
            strcpy(NewUser.Section, "Maîtrise en gestion de projet");
            break;
        }
       break;
   case 1:
       strcpy(NewUser.Faculte, "FSGA");
       printf("Choisissez une Section. \n");
       printf("0 : Certificat en Informatique\n1 : Licence en Génie Informatique\n2 : Licence en Génie Civil\n3 : Licence en Génie Électrique-Energie électrique\n4 : Licence en Génie Électrique-Télécommunications\n5 : Licence en Génie Industriel \n6 : Licence en Architecture\n7 : Licence en Génie de l'Environnement\n");
       test2=Choix(0,7,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Certificat en Informatique");
            break;
        case 1:
            strcpy(NewUser.Section, "Licence en Génie Informatique");
            break;
        case 2:
            strcpy(NewUser.Section, "Licence en Génie Civil");
            break;
        case 3:
            strcpy(NewUser.Section, "Licence en Génie Électrique-Energie électrique");
            break;
        case 4:
            strcpy(NewUser.Section, "Licence en Génie Électrique-Télécommunications");
            break;
        case 5:
            strcpy(NewUser.Section, "Licence en Génie Industriel");
            break;
        case 6:
            strcpy(NewUser.Section, "Licence en Architecture");
            break;
        case 7:
            strcpy(NewUser.Section, "Licence en Génie de l'Environnement");
            break;
        }
       break;
   case 2:
       strcpy(NewUser.Faculte, "FSAE");
       printf("Choisissez une Section. \n");
       printf("0 : Ingénieur-agronome-Entrepreneuriat et Production\n1 : Santé Publique\n2 : Technicien Supérieur en Sciences Vétérinaires et Production Animale\n");
       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Ingénieur-agronome-Entrepreneuriat et Production");
            break;
        case 1:
            strcpy(NewUser.Section, "Ingénieur-agronome-Sciences de la Vie et Technologie");
            break;
        case 2:
            strcpy(NewUser.Section, "Technicien Supérieur en Sciences Vétérinaires et Production Animale");
            break;
        }
       break;
    case 4:
       strcpy(NewUser.Faculte, " FSJP");
       printf("Choisissez une Section. \n");
       printf("0 : Certificat en Droit des affaires\n1 : Licence en Sciences Juridiques\n2 : Licence en Sciences Politiques\n");
       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Certificat en Droit des affaires");
            break;
        case 1:
            strcpy(NewUser.Section, "Licence en Sciences Juridiques");
            break;
        case 2:
            strcpy(NewUser.Section, "Licence en Sciences Politiques");
            break;
        }

       break;
    case 3:
       strcpy(NewUser.Faculte, "FSED");
       printf("Choisissez une Section. \n");
       printf("0 : Licence en Sciences de l’Éducation\n1 :  Licence d’Enseignement\n2 : Maîtrise en Sciences de l’Éducation\n3 : Licence en Relations internationales\n");
       test2=Choix(0,3,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Licence en Sciences de l’Éducation");
            break;
        case 1:
            strcpy(NewUser.Section, "Licence d’Enseignement");
            break;
        case 2:
            strcpy(NewUser.Section, "Maîtrise en Sciences de l’Éducation");
            break;
        case 3:
            strcpy(NewUser.Section, "Licence en Relations internationales");
            break;
        }
       break;
    case 5:

       strcpy(NewUser.Faculte, "FSSA");
       printf("Choisissez une Section. \n");
       printf("0 : Médecine générale\n1 : Santé Publique\n2 : Soins infirmiers avec option Maladies Infectieuses\n");
       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Médecine générale");
            break;
        case 1:
            strcpy(NewUser.Section, "Santé Publique");
            break;
        case 2:
            strcpy(NewUser.Section, "Soins infirmiers");
            break;
        }

       break;
   }
//    printf("New student infos \n");
//    printf("ID : %d\nFaculte : %s\n",NewUser.Code,NewUser.Faculte);
//    printf("Section : %s\n",NewUser.Section);
//    printf("Session : %d\n",NewUser.Session);
//    printf("Password : %s\nAnne Admission : %d\n",NewUser.Password,NewUser.AnneeAdm);
     AdmEtud(NewUser.Code , nom ,prenom,NewUser.Faculte);

    FILE *outfile;

	// open file for writing
	outfile = fopen ("Etudiant.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewUser, sizeof(struct Student), 1, outfile);

	if(fwrite != 0)
		printf("Votre etudiant a ete enregistre avec succes. ");
	else
		printf("Erreurs lors de l'enregistrement.\n");

	// close file
	fclose (outfile);



}


int AddTeacher (int id , char *nom ,char *prenom )
{
    struct Teacher NewUser;
    int test ,test2 ,cur ;


    NewUser.Code = id;
    printf("Veuillez choisir le type de professeur\n");
    printf("0 : Titulaire\n1 : Travaux Pratiques\n2 : Travaux Dirigées\n");

    cur = Choix(0,2,"Veuillez choisir parmis la liste");
    switch ((cur))
    {
    case 0:
        strcpy(NewUser.Type, "Titulaire");
        break;
    case 1:
        strcpy(NewUser.Type, "Travaux Pratiques");
        break;
    case 2:
        strcpy(NewUser.Type, "Travaux Dirigées");
        break;
    }
   printf("Veuillez choisir le nombre de cours");
   cur =0;
   NewUser.Nbcours = Choix(1,20,"Veuillez choisir une valeur entre 1 et 20");
    printf("Veuillez entrer les cours Dispenses :\n");
    char alt[100];
   for (cur = 1;cur<=NewUser.Nbcours;cur++)
   {
       printf("Entrez le cours #%d",cur);
        strcpy(alt,GetString());
        strcat(alt," - ");

   }
   strcpy(NewUser.Cours,alt);

    printf("Choisissez une Faculté. \n");
    printf("0 : Faculté des Sciences Économiques et Administratives (FSEA)\n1 : Faculté des Sciences, de Génie et d'Architecture (FSGA)\n2 : Faculté des Sciences de l’Agriculture et de l’Environnement (FSAE)\n3 : Faculté des Sciences Juridiques et Politiques (FSJP)\n4 : Faculté des Sciences de l'Education (FSED)\n5 : Faculté des Sciences de la Santé (FSSA)\n");
    test=Choix(0,5,"Veuillez choisir par la liste!");

switch ((test))
   {
   case 0:
       strcpy(NewUser.Faculte, "FSEA");
       printf("Choisissez une Section. \n");
       printf("0 : Gestion des Ressources humaines\n1 : Gestion des Affaires\n2 :Comptabilité de Management \n3 : Micro finance\n4 : Gestion de Projet\n5 :Marketing \n6 : Sciences économiques\n7 : Sciences administratives-PME\n8 : Sciences administratives-Sciences comptables\n9 : Sciences administratives-Gestion touristique\n10 : Sciences administratives-Gestion des institutions financières\n");
        printf("11 : Sciences administratives-Finance\n12 : Maîtrise en comptabilité:Contrôle-Audit\n13 : Maîtrise en gestion de projet\n");
       test2=Choix(0,13,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Gestion des Ressources humaines");
            break;
        case 1:
            strcpy(NewUser.Section, "Gestion des Affaires");
            break;
        case 2:
            strcpy(NewUser.Section, "Comptabilité de Management");
            break;
        case 3:
            strcpy(NewUser.Section, "Micro finance");
            break;
        case 4:
            strcpy(NewUser.Section, "Gestion de Projet");
            break;
        case 5:
            strcpy(NewUser.Section, "Marketing");
            break;
        case 6:
            strcpy(NewUser.Section, "Sciences économiques");
            break;
        case 7:
            strcpy(NewUser.Section, "Sciences administratives-PME");
            break;
        case 8:
            strcpy(NewUser.Section, "Sciences administratives-Sciences comptables");
            break;
        case 9:
            strcpy(NewUser.Section, "Sciences administratives-Gestion touristique");
            break;
        case 10:
            strcpy(NewUser.Section, "Sciences administratives-Gestion des institutions financières");
            break;
        case 11:
            strcpy(NewUser.Section, "Sciences administratives-Finance");
            break;
        case 12:
            strcpy(NewUser.Section, "Maîtrise en comptabilité:Contrôle-Audit");
            break;
        case 13:
            strcpy(NewUser.Section, "Maîtrise en gestion de projet");
            break;
        }
       break;
   case 1:
       strcpy(NewUser.Faculte, "FSGA");
       printf("Choisissez une Section. \n");
       printf("0 : Certificat en Informatique\n1 : Licence en Génie Informatique\n2 : Licence en Génie Civil\n3 : Licence en Génie Électrique-Energie électrique\n4 : Licence en Génie Électrique-Télécommunications\n5 : Licence en Génie Industriel \n6 : Licence en Architecture\n7 : Licence en Génie de l'Environnement\n");
       test2=Choix(0,7,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Certificat en Informatique");
            break;
        case 1:
            strcpy(NewUser.Section, "Licence en Génie Informatique");
            break;
        case 2:
            strcpy(NewUser.Section, "Licence en Génie Civil");
            break;
        case 3:
            strcpy(NewUser.Section, "Licence en Génie Électrique-Energie électrique");
            break;
        case 4:
            strcpy(NewUser.Section, "Licence en Génie Électrique-Télécommunications");
            break;
        case 5:
            strcpy(NewUser.Section, "Licence en Génie Industriel");
            break;
        case 6:
            strcpy(NewUser.Section, "Licence en Architecture");
            break;
        case 7:
            strcpy(NewUser.Section, "Licence en Génie de l'Environnement");
            break;
        }
       break;
   case 2:
       strcpy(NewUser.Faculte, "FSAE");
       printf("Choisissez une Section. \n");
       printf("0 : Ingénieur-agronome-Entrepreneuriat et Production\n1 : Santé Publique\n2 : Technicien Supérieur en Sciences Vétérinaires et Production Animale\n");
       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Ingénieur-agronome-Entrepreneuriat et Production");
            break;
        case 1:
            strcpy(NewUser.Section, "Ingénieur-agronome-Sciences de la Vie et Technologie");
            break;
        case 2:
            strcpy(NewUser.Section, "Technicien Supérieur en Sciences Vétérinaires et Production Animale");
            break;
        }
       break;
    case 4:
       strcpy(NewUser.Faculte, " FSJP");
       printf("Choisissez une Section. \n");
       printf("0 : Certificat en Droit des affaires\n1 : Licence en Sciences Juridiques\n2 : Licence en Sciences Politiques\n");
       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Certificat en Droit des affaires");
            break;
        case 1:
            strcpy(NewUser.Section, "Licence en Sciences Juridiques");
            break;
        case 2:
            strcpy(NewUser.Section, "Licence en Sciences Politiques");
            break;
        }

       break;
    case 3:
       strcpy(NewUser.Faculte, "FSED");
       printf("Choisissez une Section. \n");
       printf("0 : Licence en Sciences de l’Éducation\n1 :  Licence d’Enseignement\n2 : Maîtrise en Sciences de l’Éducation\n3 : Licence en Relations internationales\n");
       test2=Choix(0,3,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Licence en Sciences de l’Éducation");
            break;
        case 1:
            strcpy(NewUser.Section, "Licence d’Enseignement");
            break;
        case 2:
            strcpy(NewUser.Section, "Maîtrise en Sciences de l’Éducation");
            break;
        case 3:
            strcpy(NewUser.Section, "Licence en Relations internationales");
            break;
        }
       break;
    case 5:

       strcpy(NewUser.Faculte, "FSSA");
       printf("Choisissez une Section. \n");
       printf("0 : Médecine générale\n1 : Santé Publique\n2 : Soins infirmiers avec option Maladies Infectieuses\n");
       test2=Choix(0,2,"Veuillez choisir par la liste!");
        switch ((test2))
        {
        case 0:
            strcpy(NewUser.Section, "Médecine générale");
            break;
        case 1:
            strcpy(NewUser.Section, "Santé Publique");
            break;
        case 2:
            strcpy(NewUser.Section, "Soins infirmiers");
            break;
        }

       break;
   }
//    printf("New student infos \n");
//    printf("ID : %d\nFaculte : %s\n",NewUser.Code,NewUser.Faculte);
//    printf("Section : %s\n",NewUser.Section);
//    printf("NbrCOurs : %d\n",NewUser.Nbcours);
//    printf("Type : %s\n",NewUser.Type);
     AdmProf(NewUser.Code ,nom ,prenom,NewUser.Nbcours);
    FILE *outfile;

	// open file for writing
	outfile = fopen ("Professeur.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewUser, sizeof(struct Teacher), 1, outfile);

	if(fwrite != 0)
		printf("Votre etudiant a ete enregistre avec succes. ");
	else
		printf("Erreurs lors de l'enregistrement.\n");

	// close file
	fclose (outfile);



}

int AddPersonnel (int id , char *nom ,char *prenom)
{
    struct PersonAdm NewUser;
    int test ,test2 ,cur, val = 1 ;
    time_t s;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    cur = current_time->tm_year + 1900;

    NewUser.Code=id;
    printf("Veuillez entrer l'annee d'entree en fonction\n");
    NewUser.Annee=Choix(1988,cur,"Veuillez entrer une annee entre 1988 et l'annee actuelle!");

    printf("Veuillez entrer la Direction d’Affectation. \n");
    strcpy(NewUser.Affectation, GetString());

    printf("Veuillez entrer le poste. \n");
    strcpy(NewUser.Poste, GetString());

    printf("Veuillez entrer le Supérieur Hiérarchique. \n");
    strcpy(NewUser.Superieur, GetString());

   AdmPers(NewUser.Code , nom ,prenom,NewUser.Affectation,NewUser.Poste);

   printf("New personnel infos \n");
   printf("ID : %d\nAffectation : %s\n",NewUser.Code,NewUser.Affectation);
   printf("POste : %s\n",NewUser.Poste);
   printf("Superieur : %s\n",NewUser.Superieur);
   printf("Anne Admission : %d\n",NewUser.Annee);

    FILE *outfile;

	// open file for writing
	outfile = fopen ("PersonnelAdministratif.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewUser, sizeof(struct PersonAdm), 1, outfile);

	if(fwrite != 0)
		printf("Votre etudiant a ete enregistre avec succes. ");
	else
		printf("Erreurs lors de l'enregistrement.\n");

	// close file
	fclose (outfile);
}

int AddBibliothecaire (int id)
{
    struct Bibliothecaire NewUser;
    int test ,test2 ,cur ;
     time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    cur = current_time->tm_year + 1900;

    NewUser.Code=id;
    printf("Veuillez entrer l'annee d'admission\n");
    NewUser.Annee=Choix(1988,cur,"Veuillez entrer une annee entre 1988 et l'annee actuelle!");

    printf("Veuillez choisir le niveau. \n");
    printf("1 : Niveau 1 \n2 :  Niveau 2\n");
    cur = Choix(1,2,"Veuillez choisir parmis les niveaux existants");
    switch (cur)
    {
    case 1:
        strcpy(NewUser.Niveau, "N1");
        break;

    case 2:
        strcpy(NewUser.Niveau, "N2");
        break;

    }

    printf("Veuillez entrer le Supérieur Hiérarchique. \n");
    strcpy(NewUser.Superieur, GetString());

   printf("*********Received value : %d",id);

   printf("New student infos \n");
   printf("ID : %d\n",NewUser.Code);
   printf("nIVEAU : %s\n",NewUser.Niveau);
   printf("Superieur : %s\n",NewUser.Superieur);
   printf("Anne Admission : %d\n",NewUser.Annee);

    FILE *outfile;

	// open file for writing
	outfile = fopen ("Bibliothecaire.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewUser, sizeof(struct PersonAdm), 1, outfile);

	if(fwrite != 0)
		printf("Votre etudiant a ete enregistre avec succes. ");
	else
		printf("Erreurs lors de l'enregistrement.\n");

	// close file
	fclose (outfile);
}

char *GetTeacher(int code)
{
    FILE *infile;
    static char teacher[200];

    struct AdmTeacher input;

		infile = fopen ("AdministrationProf.bin", "rb");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input,sizeof(struct AdmTeacher), 1, infile))
    {
        if (code = input.Code)
            {
                strcpy(teacher,input.Prenom);
                strcat(teacher," ");
                strcat(teacher,input.Nom);
                fclose (infile);
                return teacher;
            }
    }
    printf("Professeur introuvable\n");

    printf("Choisissez 1 pour reessayer ou 2 saisir le nom du professeur\n");
    int test;
    test = Choix(1, 2, "Veuillez entrer '1' ou '2'");
    if (test==1)
    {
        GetTeacher(code);
    }
    strcpy(teacher,GetString());
    fclose (infile);
    return NULL;

}

int AddCourse()
{
    struct Cours NewCourse;
    int test;
    int test1;
    char prof[300];
    NewCourse.Code = GetLastID(2) + 1;//
    gotoxy(37,10);printf("Entrez le Titre Du cours : ");
    strcpy(NewCourse.Titre, GetString());
    gotoxy(37,11);printf("Choisissez une Faculte. \n");
    gotoxy(37,12);printf("0:FSEA-1:FSGA-2:FSAE-3:FSJP-4:FSED-5:FSSA");
    gotoxy(37,13);
    test = Choix2(0, 5, "Veuillez choisir par la liste!",37,13);
    switch (test)
    {
    case 0:
        strcpy(NewCourse.Faculte, "FSEA");
        break;
    case 1:
        strcpy(NewCourse.Faculte, "FSGA");
        break;
    case 2:
        strcpy(NewCourse.Faculte, "FSAE");
        break;
    case 3:
        strcpy(NewCourse.Faculte, "FSJP");
        break;
    case 4:
        strcpy(NewCourse.Faculte, "FSED");
        break;
    case 5:
        strcpy(NewCourse.Faculte, "FSSA");
        break;
    }
   gotoxy(37,14); printf("Choisissez le Type du cours. \n");
    gotoxy(37,15);printf("0:Obligatoire - 1:Optionnel");
    gotoxy(37+38,15);
    test = Choix2(0, 1, "Veuillez choisir parmis la liste!",37+38,15);
    switch (test)
    {
    case 0:
        strcpy(NewCourse.Type, "Obligatoire");
        break;
    case 1:
        strcpy(NewCourse.Type, "Optionnel");
        break;
    }
    test = 0;
    gotoxy(37,16);printf("Entrez le nbre de credit.(max 20)");gotoxy(37+38,16);

    NewCourse.NbCredit = Choix2(1, 20, "Veuillez choisir un nmbre de credit entre 1 et 20!",37+38,16);
    test = 0;
    gotoxy(37,17);printf("Entrez le nombre de prof (1 ou 2)"); gotoxy(37+38,17);
    test = Choix2(1, 2, "Veuillez entrer '1' ou '2'",37+38,17);
    if (test == 1)
    {
        gotoxy(37,18);printf("Entrez le code du professeur  : ");gotoxy(37+38,18);
        test1 = Choix2(1, 9999, "Veuillez verifier le format du code!",37+38,18);
        strcpy(NewCourse.Prof1, GetTeacher(test1));

    }
    else
    {
       gotoxy(37,18); printf("Entrez le code du professeur 1: ");gotoxy(37+38,18);
        test1 = Choix2(1, 9999, "Veuillez verifier le format du code!",37+38,18);
        strcpy(NewCourse.Prof1, GetTeacher(test1));
        test1=0;
        gotoxy(37,19);printf("Entrez le code du professeur 2: ");gotoxy(37+38,19);
         test1 = Choix2(1, 9999, "Veuillez verifier le format du code!",37+38,19);
        strcpy(NewCourse.Prof2, GetTeacher(test1));
    }

    //printf("Code : %d\nTitre : %s\nFaculte : %s\nType :%s\nCredit : %d\nProf : %s\n", NewCourse.Code, NewCourse.Titre, NewCourse.Faculte, NewCourse.Type, NewCourse.NbCredit,NewCourse.Prof1);
    AdmCours(NewCourse.Code, NewCourse.Titre, NewCourse.Faculte, NewCourse.NbCredit);
    FILE *outfile;

    // open file for writing
    outfile = fopen("Cours.bin", "ab");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit(1);
    }

    // write struct to file
    fwrite(&NewCourse, sizeof(struct Cours), 1, outfile);

    if (fwrite != 0)
        {gotoxy(1,26);printf("Message : Votre Cours a ete enregistre avec succes.");}
    else
       {
        gotoxy(1,26);printf("Message : Erreurs lors de l'enregistrement.\n");
       }

    // close file
    fclose(outfile);
}

int AdmProf(int code , char *nom ,char *prenom,int NbrCours)
{
    struct AdmTeacher input;
    input.Code = code;
    strcpy(input.Nom, nom);
    strcpy(input.Prenom, prenom);
    input.Nbcours = NbrCours;

    printf("Veuillez entrer le Salaire.");
    strcpy(input.Salaire, MoneyTester());
    printf("Veuillez entrer le nombre de Credit.");
    input.Nbcredit = Choix(1,100,"Choisissez une valeur de credit entre 1 et 100");


     FILE *outfile;

	// open file for writing
	outfile = fopen ("AdministrationProf.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}

	printf ("---Infos------\n -%d\n-%s\n-%s\n-%s\n-%d\n-%d\n",input.Code,input.Nom,input.Prenom,input.Salaire,input.Nbcours,input.Nbcredit);
	// write struct to file
	fwrite (&input, sizeof(struct AdmTeacher), 1, outfile);

	// close file
	fclose (outfile);

}





int AdmCours(int code , char *titre ,char *fac,int credit)
{
    struct AdmCours input;
    input.Code = code;
    input.NbCredit = credit;
    strcpy(input.Titre, titre);
    strcpy(input.Faculte, fac);
    gotoxy(37,20); printf("Veuillez entrer le cout du cours.\n");
    strcpy(input.Cout, MoneyTester2(0));
     FILE *outfile;

	// open file for writing
	outfile = fopen ("AdministrationCours.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&input, sizeof(struct AdmCours), 1, outfile);

	// close file
	fclose (outfile);

}

int AdmPers(int code , char *nom ,char *prenom,char *direction,char *fonction)
{
    struct AdmPers input;
    input.Code = code;
    strcpy(input.NomEmp, nom);
    strcpy(input.PrenomEmp, prenom);
    strcpy(input.Direction, direction);
    strcpy(input.Fonction, fonction);



    printf("Veuillez entrer le salaire de l'employe.\n");
    strcpy(input.Salaire, MoneyTester());
     FILE *outfile;

	// open file for writing
	outfile = fopen ("AdministrationPers.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}

	printf ("---Infos------\n -%d\n-%s\n-%s\n-%s\n-%s\n-%s\n",input.Code,input.NomEmp,input.PrenomEmp,input.Direction,input.Fonction,input.Salaire);
	// write struct to file
	fwrite (&input, sizeof(struct AdmPers), 1, outfile);

	if(fwrite != 0)
		printf("Enregistrement realise avec succes.\n");
	else
		printf("Erreurs lors de l'enregistrement.\n");

	// close file
	fclose (outfile);

}

int AdmEtud(int code , char *nom ,char *prenom,char *faculte)
{
    struct AdmStudent input;
    input.Code = code;
    strcpy(input.NomEtud, nom);
    strcpy(input.PrenomEtud, prenom);
    strcpy(input.Faculte, faculte);


    printf("Veuillez entrer le montant a payer.\n");
    strcpy(input.Montant, MoneyTester());
    printf("Veuillez entrer la date du prochain versement (format :xx/xx/xxxx).\n");
    strcpy(input.Date, GetDate());

     FILE *outfile;

	// open file for writing
	outfile = fopen ("AdministrationEtudiant.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}

	printf ("---Infos------\n -%d\n-%s\n-%s\n-%s\n-%s\n-%s\n",input.Code,input.NomEtud,input.PrenomEtud,input.Faculte,input.Date,input.Montant);
	// write struct to file
	fwrite (&input, sizeof(struct AdmStudent), 1, outfile);

	if(fwrite != 0)
		printf("Enregistrement realise avec succes.\n");
	else
		printf("Erreurs lors de l'enregistrement.\n");

	// close file
	fclose (outfile);

}

int AddBook()
{
struct Ouvrage NewBook;
int cur;
time_t s;
struct tm* current_time;
s = time(NULL);
current_time = localtime(&s);
cur = current_time->tm_year + 1900;

NewBook.Code = GetLastID(1)+1;
printf("Entrez la Categorie : ");
strcpy(NewBook.Categorie,GetString());
printf("Entrez la Titre : ");
strcpy(NewBook.Titre,GetString());
printf("Entrez l'Edition : ");
strcpy(NewBook.Edition,GetString());
printf("Entrez l'annee d'Edition");
NewBook.Annee=Choix(1,cur,"Veuillez entrer une annee entre 1 et l'annee actuelle!");
printf("Entrez le nombre d'Auteurs (1 ou 2):");
cur=0;
cur=Choix(1,2,"Veuillez entrer '1' ou '2'");
if (cur==1)
{
 printf("Entrez l'Auteur : ");
 strcpy(NewBook.Auteur1,GetString());
}
else
{
 printf("Entrez l'Auteur 1: ");
 strcpy(NewBook.Auteur1,GetString());
 printf("Entrez l'Auteur 2: ");
 strcpy(NewBook.Auteur1,GetString());
}

printf("Entrez le nombre de page");
NewBook.NbPage=Choix(1,9999,"Veuillez reesayer!");
NewBook.Statut = 1;


 FILE *outfile;

	// open file for writing
	outfile = fopen ("Ouvrage.bin", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opend file\n");
		exit (1);
	}


	// write struct to file
	fwrite (&NewBook, sizeof(struct Ouvrage), 1, outfile);

	if(fwrite != 0)
		printf("Votre ouvrage a ete enregistre avec succes. ");
	else
		printf("Erreurs lors de l'enregistrement.\n");

	// close file
	fclose (outfile);

}

struct NomComplet getFullName(int code)
{
    FILE *infile;

    struct NomComplet user;
    struct Utilisateur input;

    infile = fopen("Utilisateur.bin", "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    while (fread(&input, sizeof(struct Utilisateur), 1, infile))
    {
        if (code = input.Code)
        {
            strcpy(user.prenom, input.Prenom);
            strcpy(user.nom, input.Nom);
            fclose(infile);
            return user;
        }
    }
}

int Emprunt(int codeUser, int codeBook)
{
    int test;
    struct NomComplet user;
    struct Ouvrage book;
    printf("Entrez le code du livre a empruter");
    test = CheckBookAvailable(Choix(1,9999,"Verifiez le format du code"));
    if (test==0)
    {
        printf("Erreur durant l'operation d'emprunt!");
        return 0;
    }
    user = getFullName(codeUser);

    FILE *infile,*temp;

	infile = fopen ("Ouvrage.bin", "rb");
    temp = fopen ("Temp.bin", "ab");

	if (infile == NULL || temp == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&book,sizeof(struct Ouvrage), 1, infile))
    {
        if (book.Code == codeBook)
        {
            strcpy(book.PrenomEmp,user.prenom);
            strcpy(book.NomEmp,user.nom);
            book.CodeEmp = codeUser;
            strcpy(book.DateSortie, Today());
            book.Statut = 0;
        }
       fwrite(&book,sizeof(struct Ouvrage), 1, temp) ;

    }

	fclose (infile);
    fclose(temp);
    remove("Ouvrage.bin");
    rename("Temp.bin","Ouvrage.bin");

}

int CheckBookAvailable(int code)
{
    FILE *infile;

    struct Ouvrage input;

    infile = fopen("Ouvrage.bin", "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    while (fread(&input, sizeof(struct Ouvrage), 1, infile))
    {
        printf("book : %s, id :%d--<> %d\n",input.Titre,input.Code,code);
        if (code == input.Code)
        {
            if (input.Statut == 1)
            {
                printf("Le livre :%s est disponible", input.Titre);
                fclose(infile);
                return 1;
            }
            else
            {
                printf("Le livre n'est pas disponible\n");
                printf("Choisissez 0 pour reessayer ou 1 pour quitter");
                fclose(infile);
                int test;
                test=Choix(0,1,"Choisissez 0 ou 1");
                if (test==0)
                 CheckBookAvailableR(Choix(1,9999,"Verifiez le format du code"));
                return 0;
            }
        }

    }
    printf("Le livre  n'est pas a la bibliotheque.\n:");
    printf("Choisissez 0 pour reessayer ou 1 pour quitter");
                fclose(infile);
                int test;
                test=Choix(0,1,"Choisissez 0 ou 1");
                if (test==0)
                 CheckBookAvailableR(Choix(1,9999,"Verifiez le format du code"));
    return 0;
}

int Retour (int codeUser ,int codeBook)
{
     int test;
    struct Ouvrage book;
    printf("Entrez le code du livre a retourner");
    test = CheckBookAvailableR(Choix(1,9999,"Verifiez le format du code"));
    if (test==0)
    {
        printf("Erreur durant l'operation de retour!");
        return 0;
    }

    FILE *infile,*temp;

	infile = fopen ("Ouvrage.bin", "rb");
    temp = fopen ("Temp.bin", "ab");

	if (infile == NULL || temp == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&book,sizeof(struct Ouvrage), 1, infile))
    {
        if (book.Code == codeBook)
        {
            strcpy(book.PrenomEmp,"");
            strcpy(book.NomEmp,"");
            book.CodeEmp = 0;
            strcpy(book.DateRetour, Today());
            book.Statut = 1;
        }
       fwrite(&book,sizeof(struct Ouvrage), 1, temp) ;

    }

	fclose (infile);
    fclose(temp);
    remove("Ouvrage.bin");
    rename("Temp.bin","Ouvrage.bin");

}

int CheckBookAvailableR(int code)
{
    FILE *infile;

    struct Ouvrage input;

    infile = fopen("Ouvrage.bin", "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    while (fread(&input, sizeof(struct Ouvrage), 1, infile))
    {

        if (code == input.Code)
        {
            if (input.Statut == 0)
            {
                printf("Le livre a retourner est:%s", input.Titre);
                fclose(infile);
                return 1;
            }
            else
            {
                printf("Ce livre a deja ete retouurne !\n");
                printf("Choisissez 0 pour reessayer avec un autre code ou 1 pour quitter");
                fclose(infile);
                int test;
                test=Choix(0,1,"Choisissez 0 ou 1");
                if (test==0)
                 CheckBookAvailable(Choix(1,9999,"Verifiez le format du code"));
                return 0;
            }
        }

    }
    printf("Le livre  n'est pas a la bibliotheque.\n:");
    printf("Choisissez 0 pour reessayer avec un autre code ou 1 pour quitter");
                fclose(infile);
                int test;
                test=Choix(0,1,"Choisissez 0 ou 1");
                if (test==0)
                 CheckBookAvailable(Choix(1,9999,"Verifiez le format du code"));
    return 0;
}

void ReadFileUser()
{
    int id;
    FILE *infile;
	char file[20];

	struct Utilisateur input;

		infile = fopen ("Utilisateur.bin", "rb");

	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}

	while(fread(&input,sizeof(struct Utilisateur), 1, infile))
    {
        printf("Code :%d\n",input.Code);
        printf("Nom :%s\n",input.Nom);
        printf("Prenom :%s\n",input.Prenom);
        printf("NIF-CIN :%s\n",input.NIF);
		printf("Date :%s\n",input.Date);
        printf("Type:%s\n",input.Type);
        printf("Categorie :%s\n",input.Categorie);
        printf("Module : %d\n",input.Module);
		printf("----------------------\n");
    }

	fclose (infile);

}

void Report (int fileCode)
{
    FILE *infile,*temp;
	char file[20];

	struct Utilisateur input;


    infile = fopen ("Utilisateur.bin", "rb");
    temp = fopen("Report.txt","w");
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}
	fprintf(temp,"Code\tPrenom\tNom\t\n");

	while(fread(&input,sizeof(struct Utilisateur), 1, infile))
    {
        if (input.Module == fileCode)
        {
            fprintf(temp,"%d\t\t%s\t\t%s\n",input.Code,input.Prenom,input.Nom);
        }

    }
    fclose(infile);
    fclose(temp);
    switch (fileCode)
    {
    case 0:
        rename("Report.txt","ReportAdmin.txt");
        break;
    case 1:
        rename("Report.txt","ReportEtudiant.txt");
        break;
    case 2:
        rename("Report.txt","ReportProfesseurs.txt");
        break;
    case 3:
        rename("Report.txt","ReportPersonnelAdministratif.txt");
        break;
    case 4:
        rename("Report.txt","ReportBibliothecaire.txt");
        break;
    }



}

