#include <iostream>
#include <string.h>
#include <vector>
#include "CryptoMath.h"

using namespace std;

class CrytoSystem {

public:

    virtual void encrypt(int) = 0;
    virtual void decrypt(int) = 0;
    virtual void encrypt(mpz_t, mpz_t, mpz_t) = 0;
    virtual void decrypt(mpz_t, mpz_t, mpz_t) = 0;
    virtual void printKeys() = 0;
    virtual void choosePrimes(vector<int>) = 0;
    virtual void generateKeys(vector<int>) = 0;
};

class RSA: public CrytoSystem{

private:
    int p, q, n, phin, d, e;
    mpz_t P, Q, N, PHIN, D, E;

public:
    RSA(int p, int q){
        this-> p = p;
        this-> q = q;
    }

    RSA(mpz_t* primes){
        mpz_init(P);
        mpz_init(Q);
        mpz_init(N);
        mpz_init(PHIN);
        mpz_init(D);
        mpz_init(E);
        mpz_set(P, primes[0]);
        mpz_set(Q, primes[1]);
    }

    RSA(){
        
    }
    
    void getN(mpz_t n){
        mpz_init_set(n, N);
    }

    void getE(mpz_t e){
        mpz_init_set(e, E);
    }

    void getD(mpz_t d){
        mpz_init_set(d, D);
    }

    // CHECK OK
    void encrypt(int data){
        Math m;
        cout << "Encrypted Data: " << m.powMod(data, e, n) << endl;
    }

    // CHECK OK
    void encrypt(mpz_t data, mpz_t eE, mpz_t nN){
        mpz_t t;
        mpz_init_set(t, data);

        mpz_powm(data, t, eE, nN);
        gmp_printf("Encrypted DATA: %Zd\n", data);
    }

    // CHECK OK
    void decrypt(int data){
        Math m;
        cout << "Decrypted Data: " << m.powMod(data, d, n) << endl;
    }

    // CHECK OK
    void decrypt(mpz_t cipher, mpz_t dD, mpz_t nN){
        mpz_t t;
        mpz_init_set(t, cipher);

        mpz_powm(cipher, t, dD, nN);
        // gmp_printf("Decrypted DATA: %Zd\n", cipher);
    }

    // CHECK OK
    void choosePrimes(vector<int> numbers){
        int a, b = 0;
        for (int i = 0; i < numbers.size(); i++){
            cout << numbers[i] << "(" << i << ") - ";
        }
        cout << endl << "Choose any prime from above List: ";
        cin >> a;
        cin >> b;
        p = numbers[a];
        q = numbers[b];
    }

    // CHECK OK
    void generateKeys(vector<int> primes){
        choosePrimes(primes);
        phin = (p - 1) * (q - 1);
        n = p * q;
        e = 0;
        d = 0;
        Math m;

        // Find E
        for (e = 50; e <= phin; e++){
            if (m.getGCD(phin, e) == 1){
                break;
            }
        }

        // Find D
        d = n;
        while (1){
            if (((d * e) % phin) == 1){
                break;
            }
            d--;
        }
    }

    // CHECK OK
    void generateKeys(){

        mpz_t phin;
        mpz_t pTemp, qTemp;

        mpz_init_set(pTemp, P);
        mpz_init_set(qTemp, Q);

        mpz_mul(N, P, Q);
        
        Math m;
        m.calculatePHINBig(pTemp, qTemp, PHIN);

        mpz_t gcd;
        mpz_init(gcd);

        mpz_t initE;
        mpz_init_set_str(initE, "32317006071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338476170470581645852036305042887575891541065808607552399123930385521914333389668342420684974786564569494856176035326322058077805659331026192708460314150258592864177116725943603718461857357598351152334063994785580370721665417662212881203104945914551140008147396357886767669820042828793708588252247031092071155540224751031064253209884099238184688246467489498721336450133890847542", 10);

        gmp_printf("TEST: %Zd\n\n", P);

        // FIND E
        for (mpz_set(E, initE); mpz_cmp(E, PHIN) != 0; mpz_add_ui(E,E,1)){
            mpz_gcd(gcd, PHIN, E);
            if(mpz_cmp_ui(gcd, 1) == 0){
                break;
            }
        }

        // FIND D
        mpz_sub_ui(P, P, 1);
        if (mpz_invert(D,E,PHIN) == 0){
            printf("Invert does not exist\n");
        }
    }

    // CHECK OK
    void printKeys(int s){
        // cout << "PHIN: " << getphiN() << endl;
        cout << "N: " << n << endl;
        cout << "E: " << e << endl;
        cout << "D: " << d << endl;
    }

    // CHECK OK
    void printKeys(){
        gmp_printf("P: %Zd\n\n", P);
        gmp_printf("Q: %Zd\n\n", Q);
        gmp_printf("PHIN: %Zd\n\n", PHIN);
        gmp_printf("N: %Zd\n\n", N);
        gmp_printf("E: %Zd\n\n", E);
        gmp_printf("D: %Zd\n\n", D);
    }

    // ~RSA(){
    // }
};