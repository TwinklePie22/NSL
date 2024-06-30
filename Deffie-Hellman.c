#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate modular exponentiation (base^exp % modulus)
int mod_exp(int base, int exp, int modulus)
{
    int result = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp /= 2;
    }
    return result;
}

// Function to perform Diffie-Hellman Key Exchange
void diffie_hellman(int private_key, int *public_key, int P, int Q)
{
    *public_key = mod_exp(Q, private_key, P);
}

int main()
{
    int P, Q;
    int private_key_client, private_key_server;
    int public_key_client, public_key_server;
    int shared_secret_client, shared_secret_server;

    // Get user input for P and Q
    printf("Enter a prime number (P): ");
    scanf("%d", &P);
    printf("Enter another prime number (Q) to be used as primitive root modulo: ");
    scanf("%d", &Q);

    // Get user input for private keys
    printf("Enter private key for client (1 to %d): ", P - 1);
    scanf("%d", &private_key_client);
    printf("Enter private key for server (1 to %d): ", P - 1);
    scanf("%d", &private_key_server);

    //  // Generate private keys for client and server
    // private_key_client = rand() % (P - 1) + 1;
    // private_key_server = rand() % (P - 1) + 1;

    // Perform Diffie-Hellman Key Exchange for client
    diffie_hellman(private_key_client, &public_key_client, P, Q);

    // Perform Diffie-Hellman Key Exchange for server
    diffie_hellman(private_key_server, &public_key_server, P, Q);

    // Calculate shared secrets
    shared_secret_client = mod_exp(public_key_server, private_key_client, P);
    shared_secret_server = mod_exp(public_key_client, private_key_server, P);
    
    // Print keys 
    printf("\nPrime Number : P = %d\n", P);
    printf("Primitive root modulo: Q = %d\n", Q);
    printf("Private key client: %d\n", private_key_client);
    printf("Public key client: %d\n", public_key_client);
    printf("Private key server: %d\n", private_key_server);
    printf("Public key server: %d\n", public_key_server);

    // Print shared secrets
    printf("Client shared secret: %d\n", shared_secret_client);
    printf("Server shared secret: %d\n", shared_secret_server);

    return 0;
}
