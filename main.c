#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define BUFFER_SIZE 1000

// Defining all functions
void optionSelecter(int number);
struct User getAccount(char email[], char dob[]);
void openAccount();
void checkAccountBalance();
void getAccountDetails();
void delay(unsigned int mseconds);

// Defining a structure name User
struct User
{
    int flag;
    char name[50];
    char email[50];
    char dob[15];
    int accountNumber;
    int balance;
    int age;
    int verify;
    int row;
};

// Main Function
int main()
{
    int select;
    int choose;
    printf("\n\n\n\n\tUser Dashboard\n\n");
    printf("\tSELECT ONE OF THE OPTION FROM THIS [1-2]\n");
    printf("\n\t[1] Create Account\n");
    printf("\t[2] Login to Banking System\n");
    printf("\n\tSelect one of the option provided above : ");
    scanf("%d", &choose);

    if (choose == 1)
    {
        openAccount();
    }
    else
    {
        system("cls");
        char email[50];
        char dob[15];
        int balance, wait;
        printf("\t### You are gonna visit the most secure online transactions portal :) ###\n\tLogin with your credentials\n\n");
        printf("\n\n\tEnter Account Holder's Email address to login : ");
        scanf("%s", email);
        printf("\tAccount Holder's DOB [dd/mm/yyyy] for verification : ");
        scanf("%s", dob);

        struct User verifyAccount = getAccount(email, dob);
        if (verifyAccount.verify != 1)
        {
            printf("\n\tAccount Not Found or Invalid Credentials :( ");
            printf("\n\n\tPRESS INTEGER KEY TO CLEAR THE SCREEN.....");
            scanf("%d", &wait);
            system("cls");
        }
        else
        {
            system("cls");
            printf("\t Welcome %s to online Banking System , Please Wait we are loging you in... :)", verifyAccount.name);
            delay(3000);
            system("cls");
            while (1)
            {

                printf("\n\n\n\t\t ### WELCOME TO ONLINE BANKING SYSTEM ###\n\n");
                printf("\tSELECT ONE OF THE OPTION FROM THIS [1-5]\n");
                printf("\t[1] Open a account\n");
                printf("\t[2] Check account balance\n");
                printf("\t[3] Get account information\n");
                printf("\t[4] Exit\n\n");
                printf("\tSelect one of the option provided above : ");
                scanf("%d", &select);
                optionSelecter(select);
            }
        }
    }
    return 0;
}

/*
    This function find account from the database , if present then will return all the data
    or will thorw null
*/
struct User getAccount(char email[], char dob[])
{
    FILE *fp = fopen("database.csv", "r");

    if (!fp)
    {
        printf("404 FILE NOT FOUND\n");
    }

    char buffer[1024];
    int row = 0;
    int line = 0;
    int column = 0;

    while (fgets(buffer, 1024, fp))
    {

        column = 0;
        row++;
        struct User data;

        if (row == 1)
        {
            continue;
        }

        char *value = strtok(buffer, ", ");

        while (value)
        {

            if (column == 0)
            {
                strcpy(data.name, value);
            }
            if (column == 1)
            {
                data.accountNumber = atoi(value);
            }
            if (column == 2)
            {
                strcpy(data.dob, value);
            }
            if (column == 3)
            {
                data.age = atoi(value);
            }
            if (column == 4)
            {
                data.balance = atoi(value);
            }
            if (column == 5)
            {
                value = strtok(value, "\n");
                if (strcmp(dob, data.dob) == 0 && strcmp(email, value) == 0)
                {
                    data.verify = 1;
                    data.row = row;
                    return data;
                }

                else if (strcmp(email, value) == 0)
                {
                    data.flag = 1;
                    line = row;
                    strcpy(data.email, value);
                    data.row = row;
                    return data;
                }
            }
            value = strtok(NULL, ", ");
            column++;
        }
    }
    fclose(fp);
}

void openAccount()
{
    system("cls");
    printf("Let Open a account Whooo!!\n\n");

    struct User accountCreate;

    printf("\tAccount Holder's Name : ");
    scanf("%s", &accountCreate.name);
    printf("\tAccount Holder's Age : ");
    scanf("%d", &accountCreate.age);
    if (accountCreate.age < 18)
    {
        printf("\n\n\tYou are not eligible to open a account ( minimum age to open a account is 18 )");
        printf("\n\tFailed to create Account :( \n\tRestart the procedure");
        delay(5000);
        system("cls");
    }
    else
    {
        FILE *fp = fopen("database.csv", "a+");

        if (!fp)
        {
            printf("Can't open file\n");
        }

        printf("\tAccount Holder's Email-address : ");
        scanf("%s", &accountCreate.email);
        printf("\tAccount Holder's DOB ( Date of Birth )[dd/mm/yyyy] : ");
        scanf("%s", &accountCreate.dob);
        printf("\tAccount Holder's Intial Balance amount : ");
        scanf("%d", &accountCreate.balance);
        accountCreate.accountNumber = rand();

        fprintf(fp, "%s, %d, %s, %d ,%d ,%s\n", accountCreate.name,
                accountCreate.accountNumber, accountCreate.dob, accountCreate.age,
                accountCreate.balance, accountCreate.email);

        system("cls");
        printf("\n\tSuccessfully created new account !!");
        printf("\n\tEnjoy a great experience using our online banking service");
        fclose(fp);
        delay(5000);
        system("cls");
    }
}

void checkAccountBalance()
{
    system("cls");
    printf("\t### View your Account Balance ###\n\n");

    char email[50];
    int wait;
    printf("\n\n\tEnter Account Holder's Email address to view the balance : ");
    scanf("%s", email);

    struct User data = getAccount(email, "");
    if (data.flag != 1)
    {
        printf("\n\tAccount Not Found 404 :(");
        printf("\n\n\n\n\tPRESS INTEGER KEY TO CLEAR THE SCREEN.....");
        scanf("%d", &wait);
        system("cls");
    }
    else
    {
        printf("\n\n\t### Account's Details ###\n");
        printf("\n\tAccount Holder's Name : %s", data.name);
        printf("\n\tAccount Holder's account Number : %d", data.accountNumber);
        printf("\n\tAccount Current Balance : %d", data.balance);
        printf("\n\n\n\n\tPRESS INTEGER KEY TO CLEAR THE SCREEN.....");
        scanf("%d", &wait);
        system("cls");
    }
}

void getAccountDetails()
{
    system("cls");
    printf("\tGet your account Information\n\n");

    char email[50];
    int wait;
    printf("\tEnter Account Holder's Email address to get account details: ");
    scanf("%s", email);

    struct User data = getAccount(email, "");
    if (data.flag != 1)
    {
        printf("\n\tAccount Not Found 404 :(");
        printf("\n\n\tPRESS INTEGER KEY TO CLEAR THE SCREEN.....");
        scanf("%d", &wait);
        system("cls");
    }
    else
    {

        printf("\n\tAccount Holder's Name : %s", data.name);
        printf("\n\tAccount Holder's Account Number : %d", data.accountNumber);
        printf("\n\tAccount Holder's Email-address : %s", data.email);
        printf("\n\tAccount Holder's Age : %d", data.age);
        printf("\n\tAccount Holder's DOB ( Date of Birth ) : %s", data.dob);
        printf("\n\tAccount Holder's Current Balance : %d", data.balance);

        printf("\n\n\n\n\tPRESS INTEGER KEY TO CLEAR THE SCREEN.....");
        scanf("%d", &wait);
        system("cls");
    }
}

void optionSelecter(int number)
{
    switch (number)
    {
    case 1:
        openAccount();
        break;
    case 2:
        checkAccountBalance();
        break;
    case 3:
        getAccountDetails();
        break;
    case 4:
        makeTransactions();
        break;
    case 5:
        system("cls");
        printf("\n\n\t:P Have a nice day bye!! :)\n\n");
        exit(0);
    default:
        system("cls");
        printf("\n\n\tPlease select the correct number [1-5]\n");
        delay(3000);
        system("cls");
        break;
    }
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}