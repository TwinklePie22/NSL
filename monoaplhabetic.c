#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt the message using the monoalphabetic cipher
void encrypt(char *plaintext, char *key, char *ciphertext)
{
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int offset = toupper(plaintext[i]) - 'A';
            ciphertext[i] = key[offset];
            if (islower(plaintext[i]))
            {
                ciphertext[i] = tolower(ciphertext[i]);
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}

// Function to decrypt the message using the monoalphabetic cipher
void decrypt(char *ciphertext, char *key, char *plaintext)
{
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char c = toupper(ciphertext[i]);
            for (int j = 0; j < 26; j++)
            {
                if (key[j] == c)
                {
                    plaintext[i] = 'A' + j;
                    if (islower(ciphertext[i]))
                    {
                        plaintext[i] = tolower(plaintext[i]);
                    }
                    break;
                }
            }
        }
        else
        {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

int main()
{
    char plaintext[100];
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char ciphertext[100];
    char decrypted[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove the newline character

    printf("Plaintext: %s\n", plaintext);

    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt the message using Monoalphabetic Cipher
void encrypt(const char *plaintext, const char *key, char *ciphertext) {
    for (; *plaintext != '\0'; plaintext++, ciphertext++) {
        if (isalpha(*plaintext)) {
            *ciphertext = islower(*plaintext) ? tolower(key[*plaintext - 'a']) : key[*plaintext - 'A'];
        } else {
            *ciphertext = *plaintext;
        }
    }
    *ciphertext = '\0'; // Null-terminate the ciphertext
}
// Function to decrypt the message using Monoalphabetic Cipher
void decrypt(const char *ciphertext, const char *key, char *plaintext) {
    for (; *ciphertext != '\0'; ciphertext++, plaintext++) {
        if (isalpha(*ciphertext)) {
            char c = toupper(*ciphertext); // Convert to uppercase for comparison
            const char *pos = strchr(key, c);
            if (pos != NULL) {
                int index = pos - key;
                *plaintext = islower(*ciphertext) ? tolower('A' + index) : 'A' + index;
            } else {
                // Character not found in the key (e.g., punctuation), keep as is
                *plaintext = *ciphertext;
            }
        } else {
            // Non-alphabetic character, keep as is
            *plaintext = *ciphertext;
        }
    }
    *plaintext = '\0'; // Null-terminate the decrypted text
}
int main() {
    const char *key = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char plaintext[256]; // Adjust size as needed

    // Get the plaintext from the user
    printf("Enter the message to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove the newline character

    // Allocate memory for ciphertext and decrypted text
    char *ciphertext = malloc(strlen(plaintext) + 1);
    char *decrypted = malloc(strlen(plaintext) + 1);

    if (ciphertext == NULL || decrypted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    // Free allocated memory
    free(ciphertext);
    free(decrypted);

    return 0;
}
*/