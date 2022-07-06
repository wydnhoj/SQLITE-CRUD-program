#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

int create();
void retrieve();
int update();
int Delete();
int mainmenu();


int main()
{
    time_t t;
    printf("\n\n\t\tTechnological University of the Philippines\n");
    printf("\t\t\t   BSCS 2AB Final Project\n");
    printf("\t\t\tCC201 - Information Management\n");
    printf("\n\t\t\t\tPrepared by:\n");
    printf ("\t\t\t   John Ross  Ferancullo\n");
    printf ("\t\t\t   Zarene Claire Guingab\n");
    printf ("\t\t\t    Selwyn Audrey Perez\n");
    printf ("\t\t\t    Frenzy Royse  Reyes\n");
    printf ("\n");
    time(&t);
    printf ("\t\tDate today: %s", ctime(&t));
    printf ("\n");
    printf("\t\tPress any key to continue");
    getch();
    mainmenu();
}

 int mainmenu(){

    system("cls");
    printf("\t\t\t\tCASE STUDY\n");
    printf("\t\t\t\t MAIN MENU");
    int choice;
        printf("\n\n                        [1]     CREATE \n");
        printf("                        [2]     RETRIEVE \n");
        printf("                        [3]     UPDATE \n");
        printf("                        [4]     DELETE \n");
        printf("                        [5]     EXIT PROGRAM\n");
        printf("\n");
        printf("      ===============================================================\n");

        printf("\n\tChoose an appropriate number you want to perform: ");
        scanf("%d",&choice);

    switch (choice)
    {
    case 1:
        create();
        break;
    case 2:
        retrieve();
        mainmenu();
        break;
    case 3:
        update();
        break;
    case 4:
        Delete();
        break;
    case 5:
        printf("\n\n\t\tTHANK YOU! Have a nice day!\n\n");
        exit(0);
    default:
        printf("\n");
        printf("\tInvalid Choice.");
        break;
    }

return 0;
 }

int callback(void *para,int f_num,char **f_name,char **columns)
{
	int i = 0;
    printf("USER INFORMATION:\n");

	for (i = 0; i < f_num; i++)
	{
		printf("%s: %s\n", columns[i], f_name[i]);
	}
    printf("\n");
	putchar(10);

	return 0;
}


int create(){
    
    system("cls");
    sqlite3 *db;
    char *err_msg = 0;
    int id;
    int age;
    int year;
    char month[32];
    char date[32];
    char fname[32];
    char lname[32];
    char email[55];
    char sql[256];

    int a = sqlite3_open("FinalsCaseStudy.db", &db);

    if(a != SQLITE_OK){
        printf("Cannot open database: %s", sqlite3_errmsg(db));
    }
    else{
        printf("Opened database successfully!\n");
    }

    if (sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Form(ID INT, FirstName TEXT, LastName TEXT, Email TEXT, Age INT, Month TEXT, Date TEXT, Year INT)",NULL,NULL,&err_msg) != SQLITE_OK)
	{
		printf("%s\n", err_msg);
	}
	else
	{
		printf("\nTable Created.\n");
	}

    srand(time(0));
    id=rand();

    printf("\nInput first name: ");
	scanf_s("%s", &fname, 32);
	getchar();
    
    printf("\nInput last name: ");
	scanf_s("%s", &lname, 32);
	getchar();

    printf("\nInput email: ");
	scanf_s("%s", &email, 55);
	getchar();

    printf("\nInput age: ");
	scanf("%d", &age);

    printf("\nBirth month(mm): ");
    scanf_s("%s", &month, 55);
	getchar();

    printf("\nBirth date(dd): ");
    scanf_s("%s", &date, 55);
	getchar();

    printf("\nBirth year(yyyy): ");
    scanf("%d", &year);

    sprintf_s(sql,"INSERT INTO Form VALUES (%d,'%s','%s','%s',%d,'%s','%s',%d);", id, fname, lname, email, age, month, date, year, 256);

    if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) != SQLITE_OK)
	{
		printf("%s\n",err_msg);
	}
	else
	{
		printf("\nInsert done!");
	}
   
    getch();
    mainmenu();
	return 0;
}

void retrieve(){
    system("cls");
    sqlite3 *db;
    int id;
    int age;
    int year;
    char month[32];
    char date[32];
    char fname[32];
    char lname[32];
    char email[55];
    char sql[256];
    char* errmsg;

        int a = sqlite3_open("FinalsCaseStudy.db", &db);

    if(a != SQLITE_OK){
        printf("Cannot open database: %s", sqlite3_errmsg(db));
    }
    else{
        printf("\nOpened database successfully!\n\n");
    }

    sprintf_s(sql, "SELECT *FROM Form;", 256);

	if (sqlite3_exec(db, sql, callback, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
	}
	
    printf("\nPress any key to continue!");
    getch();
}

int update(){
    system("cls");
    sqlite3 *db;
    int id;
    int age;
    int year;
    char month[32];
    char date[32];
    char fname[32];
    char lname[32];
    char email[55];
	char *errmsg;
	char sql[256];

    int a = sqlite3_open("FinalsCaseStudy.db", &db);

    if(a != SQLITE_OK){
        printf("Cannot open database: %s", sqlite3_errmsg(db));
    }
    else{
        printf("Opened database successfully!\n");
    }

    retrieve();

	printf("\n\nInput id: ");
	scanf("%d", &id);
	getchar();

    printf("\nInput updated first name: ");
	scanf_s("%s", &fname, 32);
	getchar();
    
    printf("\nInput updated last name: ");
	scanf_s("%s", &lname, 32);
	getchar();

    printf("\nInput updated email: ");
	scanf_s("%s", &email, 55);
	getchar();

    printf("\nInput updated age: ");
	scanf("%d", &age);
	getchar();

    printf("\nInput updated birth month(mm): ");
    scanf_s("%s", &month, 55);
	getchar();

    printf("\nInput updated birth date(dd): ");
    scanf_s("%s", &date, 55);
	getchar();

    printf("\nInput updated birth year(yyyy): ");
    scanf("%d", &year);

	sprintf_s(sql, "UPDATE Form SET FirstName = '%s',LastName = '%s', Email = '%s', Age = %d, Month = '%s', Date = '%s', Year = %d WHERE id =%d", fname, lname, email, age, month, date, year, id, 256);

	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
	}
	else
	{
		printf("\nThe Data of ID: %d were Updated.", id);
	}

    getch();
    mainmenu();
	return 0;
}

int Delete(){
    
    system("cls");
    sqlite3 *db;
    int id;
    char *err_msg = 0;
	char sql[256];

    int a = sqlite3_open("FinalsCaseStudy.db", &db);

    if(a != SQLITE_OK){
        printf("Cannot open database: %s", sqlite3_errmsg(db));
    }
    else{
        printf("Opened database successfully!\n");
    }

    retrieve();

	printf("\nInput id: ");
	scanf("%d", &id, 6);

	sprintf_s(sql, "DELETE FROM Form WHERE id=%d", id, 256);

	if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) != SQLITE_OK)
	{
		printf("%s\n",err_msg);
	}
	else
	{
		printf("\nDELETE done!");
	}
    
    getch();
    mainmenu();
    return 0;
}