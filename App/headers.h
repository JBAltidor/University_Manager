#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 


struct Utilisateur 
{
int Code;
char NIF[20];
char Nom[50];
char Prenom[50];
char Password[50];
char Date[20];
char Type[20];
char Categorie[20]; 
int Module;//0=adm 1= etudiant , 2 = professeur , 3= comptable , 4 = agent administratif , 5= bibliothecaire
};

struct Student
{
int Code;
char Faculte[50];
char Section[100];
int Session;
int AnneeAdm;
};

struct Teacher
{
int Code;
char Faculte[50];
char Section[100];
char Type[100];
int Nbcours;
char Cours[100];
};

struct PersonAdm
{
int Code ;
char Affectation[100];
char Poste[100];
int Annee;
char Superieur[50];
};

struct Bibliothecaire
{
int Code ;
char Niveau[100];
int Annee;
char Superieur[50];
};



int GetLastID(int fileCode); // fileCode : 1= Utilisateur.dat
int GetAccess ();
void clean_stdin(void);
char *GetNIF();
char *GetString();
int inputManager();
int Choix(int min,int max , char *warning);
int AddUser ();
void ReadFileUser();
int AddStudent (int id );
int AddTeacher (int id );
int AddPersonnel (int id);
