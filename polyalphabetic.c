#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

// Function to perform Vigenere encryption or decryption
void vigenere(char *text, char *key, char *result, int encrypt)
{
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < textLen; ++i)
    {
        char shift = tolower(key[j]) - 'a';
        if (isalpha(text[i]))
        {
            char base = islower(text[i]) ? 'a' : 'A';
            char offset = encrypt ? (text[i] - base + shift) % 26 : (text[i] - base - shift + 26) % 26;
            result[i] = base + offset;
            j = (j + 1) % keyLen;
        }
        else
        {
            result[i] = text[i];
        }
    }
    result[i] = '\0';
}

int main()
{
    char plaintext[MAX_LENGTH];
    char key[MAX_LENGTH];
    char encrypted[MAX_LENGTH];
    char decrypted[MAX_LENGTH];

    printf("Enter the plaintext: ");
    fgets(plaintext, MAX_LENGTH, stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character if present

    printf("Enter the key: ");
    fgets(key, MAX_LENGTH, stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character if present

    vigenere(plaintext, key, encrypted, 1); // Encrypt
    printf("Encrypted text: %s\n", encrypted);

    vigenere(encrypted, key, decrypted, 0); // Decrypt
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}