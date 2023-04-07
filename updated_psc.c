/*
  A simple password checker that validates the strength of your password.
  Future implementations include changing into an exported function that can be built into a .dll or .so
  such that it can be imported into other code from whichever the language.
  Also it can include a simple password generator that can generate a sample password and return the string form of it
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define PASSWORD_LENGTH 8

void generatePassword(char *password, int length);
int checkPasswordStrength(char *password);

int main() {
    char name[20], password[PASSWORD_LENGTH+1];
    int choice, strength;

    printf("Enter your name: ");
    scanf("%s", name);

    printf("Do you want to enter a password or use a generated one?\n");
    printf("1. Enter a password\n");
    printf("2. Use a generated password\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter a password: ");
        scanf("%s", password);
    }
    else if (choice == 2) {
        generatePassword(password, PASSWORD_LENGTH);
        printf("Generated password: %s\n", password);
    }
    else {
        printf("Invalid choice.\n");
        return 1;
    }

    strength = checkPasswordStrength(password);
    switch (strength) {
        case 0:
            printf("Password strength: Very weak\n");
            break;
        case 1:
            printf("Password strength: Weak\n");
            break;
        case 2:
            printf("Password strength: Moderate\n");
            break;
        case 3:
            printf("Password strength: Strong\n");
            break;
        case 4:
            printf("Password strength: Very strong\n");
            break;
        case 5:
            printf("Password strength: Extremely strong\n");
            break;
        default:
            break;
    }

    return 0;
}

void generatePassword(char *password, int length) {
    char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+";
    int i, j;
    srand(time(NULL)); // Set seed for random number generator
    for (i = 0; i < length; i++) {
        j = rand() % strlen(characters); // Generate random index within characters length
        password[i] = characters[j];
    }
    password[length] = '\0'; // Add null terminator at the end
}

int checkPasswordStrength(char* password) {
    int length = strlen(password);
    int uppercase = 0, lowercase = 0, digit = 0, symbol = 0, strength = 0;

    // check for password length
    if (length >= 8) {
        strength++;
    }

    // check for uppercase letters
    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) {
            uppercase = 1;
            break;
        }
    }
    if (uppercase) {
        strength++;
    }

    // check for lowercase letters
    for (int i = 0; i < length; i++) {
        if (islower(password[i])) {
            lowercase = 1;
            break;
        }
    }
    if (lowercase) {
        strength++;
    }

    // check for digits
    for (int i = 0; i < length; i++) {
        if (isdigit(password[i])) {
            digit = 1;
            break;
        }
    }
    if (digit) {
        strength++;
    }

    // check for symbols
    for (int i = 0; i < length; i++) {
        if (!isalnum(password[i])) {
            symbol = 1;
            break;
        }
    }
    if (symbol) {
        strength++;
    }

    return strength;
}
