#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to calculate GCD (Greatest Common Divisor)
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate modular exponentiation (a^b mod n)
int modExp(int base, int exponent, int modulus)
{
    int result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

// Function to generate public and private keys
void generateKeys(int p, int q, int *n, int *e, int *d)
{
    *n = p * q;
    int phi = (p - 1) * (q - 1);
    *e = 2; // Default e value
    while (*e < phi)
    {
        if (gcd(*e, phi) == 1)
            break;
        else
            (*e)++;
    }
    // Calculate d such that (d * e) % phi == 1
    int k = 2;
    while (1)
    {
        *d = (1 + (k * phi)) / *e;
        if ((*d * *e) % phi == 1)
            break;
        else
            k++;
    }
}

// Function to encrypt a message
void encrypt(char *message, int e, int n, int *encrypted)
{
    int i;
    for (i = 0; message[i] != '\0'; ++i)
    {
        encrypted[i] = modExp(message[i], e, n);
    }
    encrypted[i] = -1; // End of encrypted message
}

// Function to decrypt a message
void decrypt(int *encrypted, int d, int n, char *decrypted)
{
    int i;
    for (i = 0; encrypted[i] != -1; ++i)
    {
        decrypted[i] = modExp(encrypted[i], d, n);
    }
    decrypted[i] = '\0'; // End of decrypted message
}

int main()
{
    int p, q, e;         // Prime numbers and public exponent
    int n, d;            // Public and private keys
    char message[100];   // Message to be encrypted
    int encrypted[100];  // Encrypted message
    char decrypted[100]; // Decrypted message

    // Input p, q, and e from user
    printf("Enter the first prime number (p): ");
    scanf("%d", &p);
    printf("Enter the second prime number (q): ");
    scanf("%d", &q);
    printf("Enter the public exponent (e): ");
    scanf("%d", &e);

    // Generate keys
    generateKeys(p, q, &n, &e, &d);

    // Input message from user
    printf("Enter the message to be encrypted: ");
    scanf(" %[^\n]", message);

    // Encrypt message
    encrypt(message, e, n, encrypted);
    printf("Encrypted message: ");
    for (int i = 0; encrypted[i] != -1; ++i)
    {
        printf("%d ", encrypted[i]);
    }
    printf("\n");

    // Decrypt message
    decrypt(encrypted, d, n, decrypted);
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}
