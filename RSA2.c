#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100

long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long modInverse(long long e, long long phi)
{
    long long m0 = phi, t, q;
    long long x0 = 0, x1 = 1;
    if (phi == 1)
        return 0;
    while (e > 1)
    {
        q = e / phi;
        t = phi;
        phi = e % phi;
        e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;
    return x1;
}

long long modExp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
void generateKeys(long long *n, long long *e, long long *d)
{
    long long p = 17, q = 13;
    *n = p * q;
    long long phi = (p - 1) * (q - 1);
    *e = 17; // Common choice for e
    *d = modInverse(*e, phi);
}
void encrypt(char *message, long long e, long long n)
{
    int len = strlen(message);
    printf("Encrypted message: ");
    for (int i = 0; i < len; i++)
    {
        long long encryptedChar = modExp(message[i], e, n);
        printf("%c", (char)encryptedChar);
    }
    printf("\n");
}

void decrypt(long long *encrypted, int size, long long d, long long n)
{
    printf("Decrypted message: ");
    for (int i = 0; i < size; i++)
    {
        long long decryptedChar = modExp(encrypted[i], d, n);
        printf("%c", (char)decryptedChar);
    }
    printf("\n");
}

int main()
{
    long long n, e, d;
    generateKeys(&n, &e, &d);
    printf("Public Key: (n: %lld, e: %lld)\n", n, e);
    printf("Private Key: (n: %lld, d: %lld)\n", n, d);
    char message[MAX_SIZE];
    printf("Enter the message to encrypt: ");
    fgets(message, MAX_SIZE, stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character if present
    encrypt(message, e, n);
    // Decrypt the message

    long long encrypted[MAX_SIZE];
    int len = strlen(message);
    for (int i = 0; i < len; i++)
    {
        encrypted[i] = modExp(message[i], e, n);
    }
    decrypt(encrypted, len, d, n);
    return 0;
}