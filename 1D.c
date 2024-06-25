#include <stdio.h>
#include <math.h>
// Power function to return value of a ^ b mod P
long long int power(long long int a, long long int b, long long int P)
{
    if (b == 1)
        return a;
    else
        return (((long long int)pow(a, b)) % P);
}

// Driver program
int main()
{
    long long int P, G, x, a, y, b, ka, kb;

    // Prompting user for input
    printf("Enter the value of prime number P: ");
    scanf("%lld", &P);
    printf("Enter the value of primitive root G: ");
    scanf("%lld", &G);
    printf("Enter the private key for User 1 (a): ");
    scanf("%lld", &a);
    printf("Enter the private key for User 2 (b): ");
    scanf("%lld", &b);

    printf("\nThe value of P : %lld\n", P);
    printf("The value of G : %lld\n\n", G);
    printf("The private key a for Alice : %lld\n", a);
    printf("The private key b for Bob : %lld\n\n", b);

    // Generating keys
    x = power(G, a, P); // Alice's generated key
    y = power(G, b, P); // Bob's generated key

    // Generating the secret key after the exchange of keys
    ka = power(y, a, P); // Secret key for Alice
    kb = power(x, b, P); // Secret key for Bob

    printf("Public key for Alice is : %lld\n", x);
    printf("Public key for Bob is : %lld\n", y);

    // Check if the secret keys match
    if (ka == kb)
    {
        printf("\nKey exchange successful!\n");
        printf("Secret key for User 1 is : %lld\n", ka);
        printf("Secret key for User 2 is : %lld\n", kb);
        return 1;
    }
    else
    {
        printf("\nKey exchange failed!\n");
        return 0;
    }
}
