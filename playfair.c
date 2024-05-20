#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

void preprocess(char *key, char *new_key)
{
    int flag[26] = {0}, len = strlen(key), j = 0;
    for (int i = 0; i < len; i++)
    {
        char offset = toupper(key[i]);
        if (offset != 'J' && !flag[offset - 'A'])
        {
            new_key[j++] = offset;
            flag[offset - 'A'] = 1;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (!flag[i] && i != 9)
        {                               
            new_key[j++] = 'A' + i;  // Skip 'J'
        }
    }
    new_key[j] = '\0';
}

void printKeyMatrix(char *new_key)
{
    printf("The Key MATRIX:\n");
    for (int i = 0; i < 25; i++)
    {
        printf("%c ", new_key[i]);
        if ((i + 1) % 5 == 0)
        {
            printf("\n");
        }
    }
}

void formatMessage(char *message)
{
    int len = strlen(message);
    char formatted[MAX_SIZE];
    int idx = 0;
    for (int i = 0; i < len; i++)
    {
        char offset = toupper(message[i]);
        if (isalpha(offset))
        {
            formatted[idx++] = offset;
            if (i + 1 < len && offset == toupper(message[i + 1]))
            {
                formatted[idx++] = 'X';
            }
        }
    }
    if (idx % 2 != 0)
    {
        formatted[idx++] = 'X';
    }
    formatted[idx] = '\0';
    strcpy(message, formatted);
}

void encrypt(char *new_key, char *message, char *cipher)
{
    int len = strlen(message), idx = 0;
    int r1, c1, r2, c2;
    for (int i = 0; i < len; i += 2)
    {
        r1 = strchr(new_key, message[i]) - new_key;
        c1 = r1 % 5;
        r1 /= 5;
        r2 = strchr(new_key, message[i + 1]) - new_key;
        c2 = r2 % 5;
        r2 /= 5;
        if (r1 == r2)
        {
            cipher[idx++] = new_key[r1 * 5 + (c1 + 1) % 5];
            cipher[idx++] = new_key[r2 * 5 + (c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            cipher[idx++] = new_key[((r1 + 1) % 5) * 5 + c1];
            cipher[idx++] = new_key[((r2 + 1) % 5) * 5 + c2];
        }
        else
        {
            cipher[idx++] = new_key[r1 * 5 + c2];
            cipher[idx++] = new_key[r2 * 5 + c1];
        }
    }
    cipher[idx] = '\0';
}

void decrypt(char *new_key, char *cipher, char *message)
{
    int len = strlen(cipher), idx = 0;
    int r1, c1, r2, c2;
    for (int i = 0; i < len; i += 2)
    {
        r1 = strchr(new_key, cipher[i]) - new_key;
        c1 = r1 % 5;
        r1 /= 5;
        r2 = strchr(new_key, cipher[i + 1]) - new_key;
        c2 = r2 % 5;
        r2 /= 5;
        if (r1 == r2)
        {
            message[idx++] = new_key[r1 * 5 + (c1 - 1 + 5) % 5];
            message[idx++] = new_key[r2 * 5 + (c2 - 1 + 5) % 5];
        }
        else if (c1 == c2)
        {
            message[idx++] = new_key[((r1 - 1 + 5) % 5) * 5 + c1];
            message[idx++] = new_key[((r2 - 1 + 5) % 5) * 5 + c2];
        }
        else
        {
            message[idx++] = new_key[r1 * 5 + c2];
            message[idx++] = new_key[r2 * 5 + c1];
        }
    }
    message[idx] = '\0';
    // Remove padding 'X' if present at the end
    if (message[idx - 1] == 'X')
    {
        message[idx - 1] = '\0';
    }
}

int main()
{
    char key[MAX_SIZE], message[MAX_SIZE], new_key[MAX_SIZE], cipher[MAX_SIZE], decrypted[MAX_SIZE];
    printf("Enter the key: ");
    fgets(key, MAX_SIZE, stdin);
    key[strcspn(key, "\n")] = '\0';
    printf("Enter the message: ");
    fgets(message, MAX_SIZE, stdin);
    message[strcspn(message, "\n")] = '\0';
    preprocess(key, new_key);

    printKeyMatrix(new_key);    // Call to print the key matrix 

    formatMessage(message);
    encrypt(new_key, message, cipher);
    printf("The encrypted message is: %s\n", cipher);
    decrypt(new_key, cipher, decrypted);
    printf("The decrypted message is: %s\n", decrypted);
    return 0;
}
