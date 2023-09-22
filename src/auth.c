#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header.h"

// Function to create a custom hash
unsigned int customHash(const char *str)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
char *USERS = "./data/users.txt";

// Simple non-cryptographic hash function
int validateInput(const char *input, size_t maxLength)
{
    if (strlen(input) > maxLength)
    {
        printf("Input is too long (maximum length: %zu characters)\n", maxLength);
        return 0; // Input is not valid
    }
    return 1; // Input is valid
}

void loginMenu(char a[MAX_USERNAME_LENGTH], char pass[MAX_PASSWORD_LENGTH])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    // Consume the newline character left in the input buffer
    while (getchar() != '\n')
        ;

    fgets(a, MAX_USERNAME_LENGTH, stdin);
    a[strcspn(a, "\n")] = '\0';

    if (!validateInput(a, MAX_USERNAME_LENGTH - 1))
    {
        return; // Input is not valid
    }

    // Disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");

    fgets(pass, MAX_PASSWORD_LENGTH, stdin);
    pass[strcspn(pass, "\n")] = '\0';

    // Restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }
}

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen(USERS, "r")) == NULL)
    {
        perror("Error! opening user file\n");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.a, userChecker.pass) != EOF)
    {
        if (strcmp(userChecker.a, u.a) == 0)
        {
            fclose(fp);
            unsigned int storedHash = customHash(userChecker.pass);
            unsigned int inputHash = customHash(u.pass);

            printf("Stored Username: %s\n", userChecker.a);
            printf("Stored Hashed Password: %u\n", storedHash);
            printf("Input Username: %s\n", u.a);
            printf("Input Hashed Password: %u\n", inputHash);

            if (storedHash == inputHash)
            {
                // Passwords match
                return "user found";
            }
            else
            {
                // Passwords don't match
                return "password incorrect";
            }
        }
    }

    fclose(fp);

    printf("No matching user found for Username: %s\n", u.a);
    return "no user found";
}