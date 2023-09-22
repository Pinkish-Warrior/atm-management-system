#include "header.h"
#include <stdio.h>
#include <string.h>

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
                  &r->userId,
                  r->accountType,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
            u.id,
            u.a,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf(RED_TEXT"\nEnter 0 to try again, 1 to return to main menu and 2 to exit:"RESET_COLOR);
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf(RED_TEXT"Insert a valid operation!\n"RESET_COLOR);
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf(GREEN_TEXT"\n✔ Success!\n\n"RESET_COLOR);
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf(RED_TEXT"Insert a valid operation!\n"RESET_COLOR);
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

    if (pf == NULL)
    {
        perror(RED_TEXT"Error opening records file"RESET_COLOR);
        exit(1);
    }

noAccount:
    system("clear");
    printf(GREEN_TEXT"\t\t\t===== New record =====\n"RESET_COLOR);

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    // Add debugging message
    // printf("Before while loop\n");

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.a) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf(RED_TEXT"✖ This Account already exists for this user\n\n"RESET_COLOR);
            goto noAccount;
        }
    }
    // Add debugging message
    // printf("After while loop\n");

    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);
    // save the account date to the file
    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf(GREEN_TEXT"\t\t====== All accounts from user, %s =====\n\n"RESET_COLOR, u.a);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.a) == 0)
        {
            printf(GREEN_TEXT"_____________________\n"RESET_COLOR);
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void readUserData(struct User users[], int *userCount)
{
    // Open the file for reading
    FILE *file = fopen("./data/users.txt", "r");

    if (file == NULL)
    {
        perror(RED_TEXT"Error opening user file"RESET_COLOR);
        exit(1);
    }

    // Initialize user count
    *userCount = 0;

    // Read user data from the file and populate the users array
    while (*userCount < MAX_USERS && fscanf(file, "%s %s", users[*userCount].a, users[*userCount].pass) == 2)
    {
        (*userCount)++;
    }

    // Close the file
    fclose(file);
}
