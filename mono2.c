#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256

void mono(char *text, char *key, char *result, int encrypt)
{
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            int offset = toupper(text[i]) - 'A';
            if (encrypt) 
                result[i] = islower(text[i]) ? tolower(key[offset]) : key[offset];
            else 
            {
                char c = toupper(text[i]);
                for (int j = 0; j < 26; j++)
                {
                    if (key[j] == c)
                    {
                        result[i] = islower(text[i]) ? 'a' + j : 'A' + j;
                        break;
                    }
                }
            }
        }
        else
        {
            result[i] = text[i];
        }
    }
    result[len] = '\0';
}

int main()
{
    char text[MAX_LEN], key[MAX_LEN], result[MAX_LEN];

    printf("Enter the text: ");
    fgets(text, MAX_LEN, stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline

    printf("Enter the key (26 uppercase letters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline

    if (strlen(key) != 26)
    {
        printf("Error: Key must be 26 characters long.\n");
        return 1;
    }

    mono(text, key, result, 1); // Encrypt
    printf("Ciphertext: %s\n", result);

    mono(result, key, result, 0); // Decrypt
    printf("Decrypted: %s\n", result);

    return 0;
}
