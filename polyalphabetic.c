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
        char shift = toupper(key[j]) - 'A';  // Convert key character to uppercase and calculate shift
        if (isalpha(text[i]))
        {
            char offset = isupper(text[i]) ? 'A' : 'a';
            result[i] = encrypt ? (text[i] - offset + shift) % 26 + offset : (text[i] - offset - shift + 26) % 26 +offset;
            j = (j + 1) % keyLen;       // Move to the next character in the key
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
    // fgets(key, MAX_LENGTH, stdin);
    // key[strcspn(key, "\n")] = '\0'; // Remove newline character if present
    scanf("%[^\n]", key);

    vigenere(plaintext, key, encrypted, 1); // Encrypt
    printf("Encrypted text: %s\n", encrypted);

    vigenere(encrypted, key, decrypted, 0); // Decrypt
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
