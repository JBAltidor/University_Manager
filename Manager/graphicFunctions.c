#include "headers.h"

char * GetPassword() {
  static char password[128];
  char c;
   int index = 0;

   /* 13 is ASCII value of Enter key */
   while((c = getch()) != 13){
       if(index < 0)
           index = 0;
       /* 8 is ASCII value of BACKSPACE character */
       if(c == 8){
           putch('\b');
           putch(NULL);
           putch('\b');
           index--;
       continue;
       }
       password[index++] = c;
       putch('*');
   }
   password[index] = '\0';

   return password;
}

///This will set the forground color for printing in a console window.
void SetColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawRectangle()
{
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < 78; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(78,0);
    printf("%c",187);
    for(i = 1; i < 25; i++){
        gotoxy(78, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(78, 25);
    printf("%c",188);
    for(i = 77; i > 0; i--){
        gotoxy(i,25);
        if(i == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(0,25);
    printf("%c",200);
    for(i = 24; i > 0; i--){
        gotoxy(0,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 1; i < 78; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 25; i++){
        gotoxy(35,i);
        printf("%c",186);
    }

}

void clearWindow()
{
    int i,j;
    for(i = 37; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}
void clearMainWindow()
{
    int i,j;
    for(i = 2; i < 35; i++){
        for(j = 7; j < 24; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}


void window()
{
    drawRectangle();
    gotoxy(28,2);
    SetColor(35);
    printf("Gestionnaire UniQ");
    gotoxy(20,3);
    printf("Universite Quisqueya, Port-au-Prince, Haiti");
    gotoxy(31,4);
    printf("Fonde en 1988");
    gotoxy(25,24);
    SetColor(17);

}

void print_heading(const char st[])
{
    SetColorAndBackground(31,28);
    gotoxy(50,8);printf("%s",st);
    SetColorAndBackground(17,15);
}
int main_window()
{
    clearMainWindow();
    int choice;
    int code =0;
    SetColor(28);
    int x = 2;


        gotoxy(x,8);printf("1. Gestion des acces");
        gotoxy(x,10);printf("2. Cours");
        gotoxy(x,12);printf("3. Administration et Comptabilite");
        gotoxy(x,14);printf("4. Bibliotheque");
        gotoxy(x,16);printf("5. Quitter le programme");
        gotoxy(x,18);printf("Faites votre choix ");
        gotoxy(x,19);printf(">>");
        choice = Choix2(1,5,"Veuillez choisir entre 1 et 5",x+3,19);
        switch(choice){
            case 1:
                clearMainWindow();
                gotoxy(x,8);printf("1. Lister les Administrateurs");
                gotoxy(x,10);printf("2. Lister les Etudiants");
                gotoxy(x,12);printf("3. Lister les Professeurs");
                gotoxy(x,14);printf("4. Lister Agents Administratifs");
                gotoxy(x,16);printf("5. Lister les Bibliothecaires");
                gotoxy(x,18);printf("6. Modifier Mot de Passe");
                gotoxy(x,20);printf("7. Sortir");
                gotoxy(x,22);printf("Faites votre choix ");
        gotoxy(x,23);printf(">>");
        choice = Choix2(1,7,"Veuillez choisir entre 1 et 7",x+3,21);
                if (choice == 7)main_window();
                print_heading("Gestion des acces");
                GAccess(choice);main_window();
                break;
            case 2:
                clearMainWindow();
                gotoxy(x,8);printf("1. Afficher les cours");
                gotoxy(x,10);printf("2. Afficher les infos d'un cours");
                gotoxy(x,12);printf("3. Ajouter un cours");
                gotoxy(x,14);printf("4. Modifier un cours");
                gotoxy(x,16);printf("5. Sortir");
                gotoxy(x,18);printf("Faites votre choix ");
        gotoxy(x,19);printf(">>");
        choice = Choix2(1,5,"Veuillez choisir entre 1 et 5",x+3,19);
                print_heading("Gestion des Cours");
                if (choice == 5)main_window();
                GCours(choice);main_window();

                return 0;
                break;
            case 3:
                clearMainWindow();
                gotoxy(x,8);printf("1. Gestion des Professeurs");
                gotoxy(x,10);printf("2. Gestion des Etudiants");
                gotoxy(x,12);printf("3. Gestion du Personnel");
                gotoxy(x,14);printf("4. Modifier un cours");
                gotoxy(x,16);printf("5. Sortir");
                gotoxy(x,18);printf("Faites votre choix ");
        gotoxy(x,19);printf(">>");
        choice = Choix2(1,5,"Veuillez choisir entre 1 et 5",x+3,19);
        print_heading("Gestion Administration & Comptabilite");

         GAdminPerson ( choice);
                return 0;
                break;
            case 4:
                clearMainWindow();
                gotoxy(x,8);printf("1. Afficher les categories");
                gotoxy(x,10);printf("2. Afficher les ouvrages");
                gotoxy(x,12);printf("3. Ajouter un ouvrage");
                gotoxy(x,14);printf("4. Emprunter un ouvrage");
                gotoxy(x,16);printf("5. Retourner un ouvrage");
                gotoxy(x,18);printf("6. Sortir");
                gotoxy(x,20);printf("Faites votre choix : ");
                return 0;
                break;
               //Leave
            case 5 :
                print_heading("Au revoir! ");
                exit(1);

        }



}
int Start(){
    ClearConsoleToColors(25,15);
    SetConsoleTitle("Gestionnaire UniQ");
    window();
    GetAccess();
    main_window();
    return 0;
}

void GAccess(int choix)
{
    switch(choix)
        {

        case 1:
            gotoxy(37,10);printf("Liste Administrateurs ");
            gotoxy(37,12);printf("Verifiez le fichier 'ReportAdmin.txt'.");
            Report(0);
            break;
        case 2:
            gotoxy(37,10);printf("Liste Etudiants ");
            gotoxy(37,12);printf("Verifiez 'ReportEtudiants.txt'.");
            Report(1);
            break;
        case 3:
            gotoxy(37,10);printf("Liste Professeurs ");
            gotoxy(37,12);printf("Verifiez 'ReportProfesseurs.txt'.");
            Report(2);
            break;
        case 4:
            gotoxy(37,10);printf("Liste Personnel Administratif ");
            gotoxy(37,12);printf("Verifiez 'ReportPersonnelAdministratif.txt'.");
            Report(3);
            break;

        case 5:
             gotoxy(37,10);printf("Liste Bibliothecaire ");
            gotoxy(37,12);printf("Verifiez 'ReportBibliothecaire.txt'.");
            Report(4);
            break;
        case 6:
             gotoxy(37,10);printf("Modifier Mot de Passe ");
             gotoxy(37,12);printf("Entrez le Code d l'utilisateur ");

             int test2;
              test2 = Choix2(1,9999,"Verifiez le format du Code!",37+32,12);

              if (CheckUserAvailability (test2)== 0)
              {
                gotoxy(1,26);printf("Cet Utilisateur n'est pas dans la base de donnees");

              }
              else
              {

                 ChangePassword(test2);
              }


            break;
        }

         gotoxy(1,27);printf("Pressez 'Enter' pour retourner");
        getch();
        gotoxy(1,26);printf("                                                           ");
        gotoxy(1,27);printf("                                                      ");
         clearWindow();


}

void PrintCours(int code)
{
    int id,i;
    FILE *infile;
	char file[20];

	struct AdmCours input;
	print_heading("Affichage des cours");

		infile = fopen ("AdministrationCours.bin", "rb");

	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit (1);
	}
	i = 2;
    if (code == 0)
    {
        gotoxy(37,10);printf("ID \t Titre Cours");
      while(fread(&input,sizeof(struct AdmCours), 1, infile))
    {
        if (input.Code<100)
        {
           gotoxy(37,10+i);printf("%d \t\t%s",input.Code,input.Titre);
        i++;
        }

    }

    }
	else
    {
         gotoxy(37,10);printf("ID   Titre  Credit  Prix");
        while(fread(&input,sizeof(struct AdmCours), 1, infile))
    {
        if (input.Code<100)
        {
            gotoxy(37,10+i);printf("%d   %s\t %d\t %s",input.Code,input.Titre,input.NbCredit,input.Cout);
            i++;
        }

    }

    }
	fclose (infile);

}

int Choix2(int min,int max , char *warning,int x,int y)
{
  char term;
  int input;
  fflush(stdin);
    //clean_stdin();

    //gotoxy(x,y);
  if (scanf("%d%c", &input, &term) == 2 && term == '\n'&& input>=min && input <= max)
   {
      gotoxy(1,26);printf("                                          ");
      gotoxy(x,y);
     return input;
   }
  else
   {
    gotoxy(1,26);printf("Message : %s",warning);
    //printf("        ");
    gotoxy(x-1,y);
    printf("        ");
    gotoxy(x,y);
    //gotoxy(2,27);printf("                                          ");
     Choix2(min,max,warning,x,y);
   }
}
char * MoneyTester()
{
    char *p;
    static char str[100];
    scanf("%s",str);
    double f = strtod(str,&p);
    if (strlen(str)==0)
    {
        gotoxy(1,26);printf("Veuillez entrer un decimal valide (format :xxxx.xx)");
        MoneyTester();
    }
    else
    {
        if (*p == 0)
        {
            strcat(str,"$");
            return str;
        }
        else
        {
            printf("Veuillez entrer un decimal valide (format :xxxx.xx)");
            MoneyTester();
        }
    }

}

char * MoneyTester2(int a)
{
    char *p;
    static char str[100];
    if (a==0)
        gotoxy(37 + 33,20);
    else if (a ==1)
        gotoxy(41,11);
    scanf("%s",str);
    double f = strtod(str,&p);
    if (strlen(str)==0)
    {
        gotoxy(1,26);printf("Veuillez entrer un decimal valide (format :xxxx.xx)");
        MoneyTester();
    }
    else
    {
        if (*p == 0)
        {
            strcat(str,"$");
            return str;
        }
        else
        {
            printf("Veuillez entrer un decimal valide (format :xxxx.xx)");
            MoneyTester();
        }
    }

}
