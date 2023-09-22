#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isUsernameTaken(const char *username);
void addUserToDatabase(const char *username, const char *password);

void setTextColor(const char *color)
{
    printf("%s", color);
}

void updateAccountInfo(struct User u)
{
    printf("\nUpdating Account Information\n");
    // Prompt the user for the updated information
    printf("Enter new name: ");
    scanf("%s", u.a);
    printf("Enter new password: ");
    scanf("%s", u.pass);

    // Update the user's account information in the database or file

    printf("\nAccount information updated successfully!\n");
}

void checkAccountDetails(struct User u)
{
    printf("\nChecking Account Details\n");
    // Retrieve and display the account details for the user from the database or file

    printf("Account ID: %d\n", u.id);
    printf("Name: %s\n", u.a);
    // Display other account details (e.g., balance, transaction history, etc.)

    printf("\nAccount details displayed successfully!\n");
}

void makeTransaction(struct User u)
{
    printf("\nMaking a Transaction\n");
    // Prompt the user for transaction details
    double amount;
    printf("Enter the transaction amount: ");
    scanf("%lf", &amount);

    // Perform the transaction (e.g., deduct amount from balance, update transaction history)

    printf("\nTransaction completed successfully!\n");
}

void removeAccount(struct User u)
{
    printf("\nRemoving an Account\n");
    // Confirm the user's intention to remove the account
    printf("Are you sure you want to remove your account? (Y/N): ");
    char choice;
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
        // Perform the account removal process (e.g., delete account from the database or file)
        printf("\nAccount removed successfully!\n");
    }
    else
    {
        printf("\nAccount removal canceled.\n");
    }
}

void registerMenu(char a[50], char pass[50])
{

    system("clear");
    printf("\n\n\t\t======= Registration =======\n\n");

    printf("\nEnter your username: ");
    scanf("%s", a);

    // Check if the username already exists
    if (isUsernameTaken(a))
    {
        printf("Username already exists. Please choose a different username.\n");
        return;
    }

    printf("Enter your password: ");
    scanf("%s", pass);

    // Create a new user entry and save it to the users.txt file
    addUserToDatabase(a, pass);

    printf("Registration successful. You can now login with your new account.\n");
}

bool isUsernameTaken(const char *username)
{
    // Implement the logic to check if the username exists in your data structure
    // For simplicity, I'll use a static array as an example.
    static const char *registeredUsernames[] = {"user1", "user2", "user3"};

    for (int i = 0; i < sizeof(registeredUsernames) / sizeof(registeredUsernames[0]); i++)
    {
        if (strcmp(username, registeredUsernames[i]) == 0)
        {
            return true; // Username already taken
        }
    }

    return false; // Username is not taken
}

void addUserToDatabase(const char *username, const char *password)
{
    // Implement the logic to add a new user to your database or data structure
    // For simplicity, I'll print the added user's details as an example.
    printf("Added user to the database:\n");
    printf("Username: %s\n", username);
    printf("Password: %s\n", password);
}

void transferOwnership(struct User u)
{
    printf("\nTransferring Ownership\n");
    // Prompt the user for the necessary information to transfer ownership of an account
    char recipientName[50];
    printf("Enter the recipient's username: ");
    scanf("%s", recipientName);

    // Perform the ownership transfer process (e.g., update the account owner in the database or file)

    printf("\nOwnership transferred successfully!\n");
}

void mainMenu(struct User u)
{
    int option;
    system("clear");
    printf(RED_TEXT "\n\n\t\t========================== \xF0\x9F\x8F\xA7 =========================\n\n" RESET_COLOR);
    setTextColor(GREEN_TEXT);
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    setTextColor(RESET_COLOR);
    printf(RED_TEXT "\n\t\t[8]- Exit\n" RESET_COLOR);
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        // student TODO : add your **Update account information** function
        updateAccountInfo(u);
        break;
    case 3:
        // student TODO : add your **Check the details of existing accounts** function
        checkAccountDetails(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // student TODO : add your **Make transaction** function
        makeTransaction(u);
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        removeAccount(u);
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        transferOwnership(u);
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n \xE2\x9A\xA0");
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    const char *result = NULL;

    system("clear");
    setTextColor(BLUE_TEXT);
    printf("\n\n\t\t================ \xF0\x9F\x8F\xA7 ================\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1] - login\n");
    printf("\n\t\t[3] - register\n");
    setTextColor(RESET_COLOR);
    printf(RED_TEXT "\n\t\t[3]- exit\n" RESET_COLOR);

    while (!r)
    {
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            loginMenu(u->a, u->pass);
            result = getPassword(*u); // Assign a value to result here

            printf("Before getPassword\n"); // Debugging message

            if (strcmp(result, "user found") == 0)
            {
                printf("\n\nPassword Match!");
                r = 1;
                printf("After getPassword\n"); // Debugging message
            }
            else if (strcmp(result, "password incorrect") == 0)
            {
                printf("\nWrong password!! or User Name\n");
                printf("1 - Try again\n2 - Exit\n");
                // exit(1);
            }
            else if (strcmp(result, "no user found") == 0)
            {
                printf("\nNo matching user found for Username: %s\n", u->a);
                // exit(1);
            }
            break;
        case 2:
            // Call the registerMenu function to register a new user
            registerMenu(u->a, u->pass);
            printf(GREEN_TEXT "\n\nRegistration Successful! \xF0\x9F\x92\xAF" RESET_COLOR);
            r = 1;
            break;
            exit(1);
            break;
        case 3:
            printf("Goodbye \xF0\x9F\x91\x8B");
            exit(0);
            break;
        default:
            printf("Insert a valid operation! \xF0\x9F\x93\x9B\n");
        }
    }
}

int main()
{
    struct User u;

    printf(GREEN_TEXT "Welcome to the ATM!\n" RESET_COLOR);

    initMenu(&u);
    mainMenu(u);
    return 0;
}