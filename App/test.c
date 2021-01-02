#include "headers.h"

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
    printf("Entrez le Titre Du cours : ");
    strcpy(NewCourse.Titre, GetString());
    printf("Choisissez une Faculte. \n");
    printf("0 : Faculté des Sciences Économiques et Administratives (FSEA)\n1 : Faculté des Sciences, de Génie et d'Architecture (FSGA)\n2 : Faculté des Sciences de l’Agriculture et de l’Environnement (FSAE)\n3 : Faculté des Sciences Juridiques et Politiques (FSJP)\n4 : Faculté des Sciences de l'Education (FSED)\n5 : Faculté des Sciences de la Santé (FSSA)\n");
    test = Choix(0, 5, "Veuillez choisir par la liste!");
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
    printf("Choisissez le Type du cours. \n");
    printf("0 : Obligatoire\n1 : Optionnel\n");
    test = Choix(0, 1, "Veuillez choisir parmis la liste!");
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
    printf("Veuillez entrer le nombre de credit du cours (max 20)\n");
    NewCourse.NbCredit = Choix(1, 20, "Veuillez choisir un nmbre de credit entre 1 et 20!");
    test = 0;
    printf("Entrez le nombre de professeur (1 ou 2):");
    
    test = Choix(1, 2, "Veuillez entrer '1' ou '2'");
    if (test == 1)
    {
        printf("Entrez le code du professeur  : ");        
        test1 = Choix(1, 9999, "Veuillez verifier le format du code!");
        strcpy(NewCourse.Prof1, GetTeacher(test1));
        
    }
    else
    {
        printf("Entrez le code du professeur 1: ");
        test1 = Choix(1, 9999, "Veuillez verifier le format du code!");
        strcpy(NewCourse.Prof1, GetTeacher(test1));
        test1=0;
        printf("Entrez le code du professeur 2: ");
         test1 = Choix(1, 9999, "Veuillez verifier le format du code!");
        strcpy(NewCourse.Prof2, GetTeacher(test1));
    }

    printf("Code : %d\nTitre : %s\nFaculte : %s\nType :%s\nCredit : %d\nProf : %s\n", NewCourse.Code, NewCourse.Titre, NewCourse.Faculte, NewCourse.Type, NewCourse.NbCredit,NewCourse.Prof1);
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
        printf("Votre Cours a ete enregistre avec succes.\n");
    else
        printf("Erreurs lors de l'enregistrement.\n");

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
	
	if(fwrite != 0) 
		printf("Enregistrement realise avec succes.\n"); 
	else
		printf("Erreurs lors de l'enregistrement.\n"); 

	// close file 
	fclose (outfile); 

}





