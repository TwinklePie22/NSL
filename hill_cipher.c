#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 3
#define MAX_SIZE 100

void getKeyMatrix(int keyMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    printf("Enter the key matrix (3x3):\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            scanf("%d", &keyMatrix[i][j]);
        }
    }
}

void formatMessage(char *message) {
    int len = strlen(message), j = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            message[j++] = toupper(message[i]);
        }
    }
    message[j] = '\0';
}

void encryptMessage(int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *message) {
    int len = strlen(message);
    int vector[MATRIX_SIZE];

    // Pad message to ensure its length is a multiple of MATRIX_SIZE
    while (len % MATRIX_SIZE != 0) {
        message[len++] = 'X';
    }
    message[len] = '\0';

    for (int i = 0; i < len; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            vector[j] = message[i + j] - 'A';
        }

        for (int j = 0; j < MATRIX_SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += keyMatrix[j][k] * vector[k];
            }
            message[i + j] = (sum % 26) + 'A';
        }
    }
}

int main() {
    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE];
    char message[MAX_SIZE];

    getKeyMatrix(keyMatrix);

    printf("Enter the message to encrypt (up to 100 characters): ");
    scanf(" %[^\n]", message);

    formatMessage(message);
    encryptMessage(keyMatrix, message);

    printf("Encrypted message: %s\n", message);

    return 0;
}