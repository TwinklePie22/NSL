#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

#define MAX_PLAINTEXT_LENGTH 1024
#define AES_BLOCK_SIZE 16

// Function to encrypt plaintext using AES
void aes_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, AES_BLOCK_SIZE);  // Initialize IV to zero
    
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &aes_key, iv, AES_ENCRYPT);
}

// Function to decrypt ciphertext using AES
void aes_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *decryptedtext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, AES_BLOCK_SIZE);  // Initialize IV to zero
    
    AES_cbc_encrypt(ciphertext, decryptedtext, ciphertext_len, &aes_key, iv, AES_DECRYPT);
}

// Function to safely get input from user
int get_input(char *prompt, unsigned char *buffer, int max_length) {
    printf("%s", prompt);
    int ch;
    // Flush only the newline characters if they are the first in the buffer
    while ((ch = getchar()) == '\n');

    if (ch != EOF) {
        ungetc(ch, stdin);  // Put back the first non-newline character
    }

    if (fgets((char *)buffer, max_length, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 0;
    }

    // Remove any trailing newline character from the input
    size_t len = strlen((char *)buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return strlen((char *)buffer);
}

int main() {
    unsigned char key[AES_BLOCK_SIZE + 1];  // +1 for null terminator
    unsigned char plaintext[MAX_PLAINTEXT_LENGTH];
    unsigned char ciphertext[MAX_PLAINTEXT_LENGTH + AES_BLOCK_SIZE];  // Allow for padding
    unsigned char decryptedtext[MAX_PLAINTEXT_LENGTH + AES_BLOCK_SIZE];
    int plaintext_len = 0;
    
    // Get key from user
    do {
        if (get_input("Enter 16-character AES key: ", key, sizeof(key)) != AES_BLOCK_SIZE) {
            printf("Error: Key must be exactly 16 characters long. Please try again.\n");
        }
    } while (strlen((char *)key) != AES_BLOCK_SIZE);

    // Get plaintext from user
    do {
        plaintext_len = get_input("Enter plaintext (max 1023 characters): ", plaintext, sizeof(plaintext));
        if (plaintext_len == 0) {
            fprintf(stderr, "Warning: Plaintext is empty. Please enter some text.\n");
        }
    } while (plaintext_len == 0);
    
    int padded_len = ((plaintext_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // Pad the plaintext
    memset(plaintext + plaintext_len, 0, padded_len - plaintext_len);
    
    // Encrypt the plaintext
    aes_encrypt(plaintext, padded_len, key, ciphertext);
    
    // Decrypt the ciphertext
    aes_decrypt(ciphertext, padded_len, key, decryptedtext);
    
    printf("Original message: %s\n", plaintext);
    printf("Encrypted message: ");
    for (int i = 0; i < padded_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted message: %s\n", decryptedtext);
    
    return 0;
}