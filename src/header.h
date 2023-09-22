#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_USERS 100 // Adjust the maximum number of users as needed
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// ANSI escape codes for colors
#define RED_TEXT "\x1b[31m"
#define GREEN_TEXT "\x1b[32m"
#define BLUE_TEXT "\x1b[34m"
#define RESET_COLOR "\x1b[0m"

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char a[50];
    char pass[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
// Function to set text color
void setTextColor(const char *color);

#endif // HEADER_H