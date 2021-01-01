#include "headers.h"

int Bibliothecaire (int id)
{
    struct Bibliothecaire NewUser;
    int test ,test2 ,cur ;
     time_t s, val = 1;
    struct tm* current_time;    
    s = time(NULL);    
    current_time = localtime(&s); 
    cur = current_time->tm_year + 1900;
   

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

   
    
   printf("New student infos \n");
   printf("ID : %d\nAffectation : %s\n",NewUser.Code);
   printf("nIVEAU : %s\n",NewUser.Niveau);
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
