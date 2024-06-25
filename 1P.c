#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
void encrypt(char *plaintext, char *key) {
    int key_len = strlen(key);
    int plaintext_len = strlen(plaintext);
    int i;
    for(i = 0; i < plaintext_len; i++) {
        if(isalpha(plaintext[i])) {
            int shift = tolower(key[i % key_len]) - 'a';
            if(isupper(plaintext[i])) {
                plaintext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
            } else {
                  plaintext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
            }
        }
    }
}

void decrypt(char *ciphertext, char *key) {
    int key_len = strlen(key);
    int ciphertext_len = strlen(ciphertext);
    int i;
    for(i = 0; i < ciphertext_len; i++) {
        if(isalpha(ciphertext[i])) {
            int shift = tolower(key[i % key_len]) - 'a';
            if(isupper(ciphertext[i])) {
                ciphertext[i] = (ciphertext[i] - 'A' - shift + 26) % 26 + 'A';
            } else {
                ciphertext[i] = (ciphertext[i] - 'a' - shift + 26) % 26 + 'a';
            }
        }
    }
}

int main() {
char plaintext[1000];
char key[100];

printf("Enter the plaintext: ");
fgets(plaintext, sizeof(plaintext), stdin);

printf("Enter the key: ");
fgets(key, sizeof(key), stdin);

// Remove newline characters
plaintext[strcspn(plaintext, "\n")] = '\0';
key[strcspn(key, "\n")] = '\0';

// Encrypt the messagewear
encrypt(plaintext, key);
printf("Encrypted text: %s\n", plaintext);

// Decrypt the message
decrypt(plaintext, key);
printf("Decrypted text: %s\n", plaintext);

return 0;
}
