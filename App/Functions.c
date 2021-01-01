#include "headers.h"
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);

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
	
	
	fclose (infile);
	return id; 
}

char *GetString()
{
    static char text[50];
    int val;
     val = scanf("%s",text);
     if (val != 1)
     {
      printf("Ce champ est obligatoire .");
	  clean_stdin();
      GetString();    
     }
     return text;

}

int GetAccess ()

{
	FILE *infile;
	struct Utilisateur input;

	char code[20];
	int user;
	
	printf ("\nEntrez votre Code d'acces :");
	scanf("%d",&user);
	
	clean_stdin();
	printf ("\nEntrez votre mot de passe:");
	gets(code);
	
	infile = fopen ("Utilisateur.bin", "rb"); 
	if (infile == NULL) 
	{ 
		fprintf(stderr, "\nError opening file\n"); 
		exit (1); 
	} 
	
	while(fread(&input,sizeof(struct Utilisateur), 1, infile)) 
	{
		if (user ==input.Code )
		{
			if (strcmp(code, input.Password)== 0)
			{
				printf("\nBienvenue %s",input.Prenom);
				return 1;
			}
			else return 0;
		}
		
	}
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
  

  printf("\n>>");
  

  if (scanf("%d%c", &input, &term) == 2 && term == '\n'&& input>=min && input <= max)
   {  
     return input;
   }
  else
   {
    printf("%s\n",warning);
    clean_stdin();
     Choix(min,max,warning);
   }  
}

int AddUser ()
{
struct Utilisateur NewUser;
int test;

NewUser.Code = GetLastID(1)+1;
strcpy(NewUser.NIF,GetNIF());
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
	   AddStudent(NewUser.Code);
       break;
   case 2:
       strcpy(NewUser.Categorie, "Professeur");
	   AddTeacher(NewUser.Code);
       break;
    case 3:
       strcpy(NewUser.Categorie, "Agent Administratif");
       AddPersonnel (NewUser.Code);
       break;
    case 4:
       strcpy(NewUser.Categorie, "Bibliothecaire");
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



int AddStudent (int id )
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


int AddTeacher (int id  )
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
   for (cur = 0;cur<=NewUser.Nbcours;cur++)
   {
       printf("Entrez le cours #%d",cur+1);
      // #TODO add cours

   }
   

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

int AddPersonnel (int id)
{
    struct PersonAdm NewUser;
    int test ,test2 ,cur ;
     time_t s, val = 1;
    struct tm* current_time;    
    s = time(NULL);    
    current_time = localtime(&s); 
    cur = current_time->tm_year + 1900;
   

    printf("Veuillez entrer l'annee d'admission\n");
    NewUser.Annee=Choix(1988,cur,"Veuillez entrer une annee entre 1988 et l'annee actuelle!");

    printf("Veuillez entrer la Direction d’Affectation. \n");
    strcpy(NewUser.Affectation, GetString());

    printf("Veuillez entrer le poste. \n");
    strcpy(NewUser.Poste, GetString());

    printf("Veuillez entrer le Supérieur Hiérarchique. \n");
    strcpy(NewUser.Superieur, GetString());

   
    
   printf("New student infos \n");
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