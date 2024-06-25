#include <math.h>
#include <stdio.h>


int gcd(int a , int b){
    int temp;
    while(1){
        temp = a % b;
        if(temp == 0){
            return b;
        }
        
        a = b;
        b = temp;
    }
}

int modinverse(int e , int phi){
    e = e % phi;
    
    for(int x = 1 ; x < phi ; x++){
        if((x * e) % phi == 1) return x;
    }
    
    return -1;
}

long long exponential(long long base , long long expo , long long mod){
    long long result = 1;
    base %= mod;
    
    while(expo > 0){
        if(expo % 2 == 1){
            result = (result * base) % mod;
        }
        
        base = (base * base )% mod;
        expo /= 2;
    }
    
    return result;
}


int main() {
    int p , q , e , m;
    
    printf("Enter the value of p: ");
    scanf("%d" , &p);
    
    printf("Enter the value of q: ");
    scanf("%d" , &q);
    
    printf("Enter the value of e: ");
    scanf("%d" , &e);
    
    printf("Enter the message: ");
    scanf("%d" , &m);
    
    int n = p * q;
    int phi = (p-1)*(q-1);
    
    while(e < phi){
        if(gcd(e , phi) == 1){
            break;
        }
        else{
            e++;
        }
    }
    
    int d = modinverse(e , phi);
    
    if(d == -1){
        printf("No Modulo found inverse ");
        return -1;
    }
    
    long long c = exponential(m , e , n);
    printf("Encrypted data is: %lld\n " , c);
    
    long long m1 = exponential(c , d , n);
    printf("Decrypted data is: %lld\n " , m1);

    return 0;
}
