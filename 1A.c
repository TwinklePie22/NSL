#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <string.h>

// Function to handle errors
void handleErrors(void) {
    fprintf(stderr, "An error occurred\n");
    exit(1);
}

// Function to encrypt a message
void aes_encrypt(const unsigned char *message, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    AES_KEY encryptKey;
    AES_set_encrypt_key(key, 128, &encryptKey);
    AES_cbc_encrypt(message, ciphertext, strlen((const char *)message) + 1, &encryptKey, iv, AES_ENCRYPT);
}

// Function to decrypt a message
void aes_decrypt(unsigned char *ciphertext, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    AES_KEY decryptKey;
    AES_set_decrypt_key(key, 128, &decryptKey);
    AES_cbc_encrypt(ciphertext, plaintext, AES_BLOCK_SIZE, &decryptKey, iv, AES_DECRYPT);
}

int main() {
    // Message to encrypt
    unsigned char message[] = "welcome to ISE";

    // Buffer for the ciphertext and plaintext
    unsigned char ciphertext[AES_BLOCK_SIZE * ((sizeof(message) + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE)];
    unsigned char decryptedtext[AES_BLOCK_SIZE * ((sizeof(message) + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE)];

    // Key and IV (Initialization Vector)
    unsigned char key[16], iv[16];

    // Generate random key and IV
    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) {
        handleErrors();
    }

    printf("Original message: %s\n", message);

    // Encrypt the message
    aes_encrypt(message, key, iv, ciphertext);
    printf("Encrypted message: ");
    for (int i = 0; i < sizeof(ciphertext); i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // Decrypt the message
    aes_decrypt(ciphertext, key, iv, decryptedtext);
    printf("Decrypted message: %s\n", decryptedtext);

    return 0;
}
