#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define MAX_LEN 2048

void handle_errors() {
    ERR_print_errors_fp(stderr);
    abort();
}

RSA *generate_rsa_key() {
    RSA *rsa = NULL;
    BIGNUM *bne = NULL;
    
    int bits = 2048;
    unsigned long e = RSA_F4;

    bne = BN_new();
    if (bne == NULL || BN_set_word(bne, e) != 1) {
        handle_errors();
    }

    rsa = RSA_new();
    if (rsa == NULL || RSA_generate_key_ex(rsa, bits, bne, NULL) != 1) {
        handle_errors();
    }

    BN_free(bne);
    return rsa;
}

int main() {
    RSA *rsa_A = NULL, *rsa_B = NULL;
    unsigned char plaintext[MAX_LEN];
    unsigned char ciphertext[MAX_LEN] = {0};
    unsigned char decryptedtext[MAX_LEN] = {0};
    int encrypted_len, decrypted_len;

    // Initialize OpenSSL
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();

    // Key Generation for User A
    rsa_A = generate_rsa_key();
    if (rsa_A == NULL) {
        fprintf(stderr, "Error generating RSA key for User A\n");
        handle_errors();
    }

    // Key Generation for User B
    rsa_B = generate_rsa_key();
    if (rsa_B == NULL) {
        fprintf(stderr, "Error generating RSA key for User B\n");
        RSA_free(rsa_A);
        handle_errors();
    }

    // Input message from user
    printf("Enter the message to encrypt: ");
    if (!fgets((char *)plaintext, MAX_LEN, stdin)) {
        fprintf(stderr, "Error reading input\n");
        RSA_free(rsa_A);
        RSA_free(rsa_B);
        EVP_cleanup();
        ERR_free_strings();
        return 1;
    }

    // Remove newline character from input
    plaintext[strcspn((char *)plaintext, "\n")] = '\0';

    // Encryption by User A (using B's public key)
    encrypted_len = RSA_public_encrypt(strlen((char *)plaintext), plaintext, ciphertext, rsa_B, RSA_PKCS1_OAEP_PADDING);
    if (encrypted_len == -1) {
        fprintf(stderr, "Error encrypting message\n");
        handle_errors();
    }

    // Decryption by User B
    decrypted_len = RSA_private_decrypt(encrypted_len, ciphertext, decryptedtext, rsa_B, RSA_PKCS1_OAEP_PADDING);
    if (decrypted_len == -1) {
        fprintf(stderr, "Error decrypting message\n");
        handle_errors();
    }

    printf("\nOriginal message: %s\n", plaintext);
    printf("Encrypted message: ");
    for (int i = 0; i < encrypted_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted message: %s\n", decryptedtext);

    // Clean up
    RSA_free(rsa_A);
    RSA_free(rsa_B);
    EVP_cleanup();
    ERR_free_strings();

    return 0;
}
