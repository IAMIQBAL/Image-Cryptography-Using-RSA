#include <iostream>
#include <vector>
#include <cmath>
#include <gmpxx.h>

using namespace std;

class Math {

private:

public:
    bool isPrime(int n){ 
        // Corner case 
        if (n <= 1){
            return false;
        } 
    
        // Check from 2 to n-1 
        for (int i = 2; i < n; i++){
            if (n % i == 0){
                return false; 
            }
        }

        return true; 
    }

    bool isFactor(int x, int y){
        if (x % y == 0){
            return true;
        }
        return false;
    }

    int powMod(int data, int key, int n) {

        long int enc = 1, temp = data;

        for (;key > 0;key/=2) {
            if (key % 2 == 1){
                enc = (enc * temp) % n;
            }
            temp = (temp * temp) % n;
        }

        return enc % n;
    }

    int getGCD(int num1, int num){
        // Greatest common divisor
        int gcd = 0;
        for (int i = 1; i <= num1 && i <= num; ++i){
            if (num1 % i == 0 && num % i == 0){
                gcd = i;
            }
        }
        return gcd;
    }

    void calculatePHINBig(mpz_t p, mpz_t q, mpz_t phin){

        mpz_init(phin);
        mpz_set_ui(phin, 0);
        
        mpz_sub_ui(p,p,1);
        mpz_sub_ui(q,q,1);

        mpz_mul(phin,p,q);
    }   
};


class PrimeTest: public Math {

private:
    unsigned long long int p;
    mpz_t p_gmp;
public:
    PrimeTest(){

    }

    PrimeTest(unsigned long long int p){
        this-> p = p;
    }

    PrimeTest(mpz_t p_gmp1){
        mpz_init_set(p_gmp, p_gmp1);
    }

    // CHECK OK BUT SLOW
    // (a ^ p) - a = multiple of a
    bool fermatsTest(){
        mpz_t a;
        mpz_t m, n;

        mpz_init(a);
        
        for (mpz_set_d(a, 1);mpz_cmp_ui(a, p) < 0;){

            mpz_init(m);
            mpz_init(n);
            
            mpz_pow_ui(m, a, p);
            mpz_sub(n, m, a);
            gmp_printf("TEST: %Zd\n", n);

            if (mpz_mod_ui(n, n, p) != 0){
                return false;
            }
            mpz_add_ui(a, a, 1);
        }
        return true;
    }

    // CHECK OK
    bool millerRabinsTest(){
        int n = mpz_probab_prime_p(p_gmp, 25);
        if (n == 2 || n == 1){
            return 1;
        } else {
            return 0;
        }
    }
};

class PrimeGenerate: public Math{

private:
    int pInit, limit, maxRange, iter;
    mpz_t currPrime;
public:
    
    PrimeGenerate(){
        pInit = 0;
        limit = 0;
    }

    PrimeGenerate(int pInit, int limit){
        this-> pInit = pInit;
        this-> limit = limit;
        maxRange = 0;
    }

    PrimeGenerate(int maxRange){
        this-> maxRange = maxRange;
    }

    PrimeGenerate(mpz_t currPrime1, int iter){
        mpz_init_set(currPrime, currPrime1);
        this-> iter = iter;
    }
    
    // CHECK OK
    int mersennePrime(){
        int pGen = 0;
        int p = pInit;
        while (p < limit){
            if (isPrime(pInit)){
                pGen = pow(2, p);
                pGen--;
                cout << pGen << endl;
            }
            p++;
        }
        return pGen;
    }

    //CHECK OK
    void mersennePrime(mpz_t holder){
        mpz_t pGen;
        unsigned long long int p = pInit;
        mpz_t base;

        mpz_init_set_ui(pGen, 0);
        // mpz_init_set_ui(p, pInit);
        mpz_init_set_str(base, "2", 10);

        while (p < limit){
            if (isPrime(pInit)){
                mpz_pow_ui(pGen, base, p);
                mpz_sub_ui(pGen, pGen, 1);
            }
            p++;
        }
        mpz_init_set(holder, pGen);
    }

    // CHECK OK
    vector<int> SieveOfEratosthenes(){
        vector<int> primes;
        int pArr[maxRange];
        for (int i = 0; i < maxRange; i++){
            pArr[i] = 1;
        } 
    
        for(int p = 2; p*p <= maxRange; p++) { 
            if (pArr[p] == true) {
                for(int i = p*p; i<= maxRange; i += p) 
                    pArr[i] = false; 
            } 
        } 
    
        for(int p = 2; p <= maxRange; p++) 
            if(pArr[p]){
                // cout << p << endl;
                primes.push_back(p);
            }
            
        return primes;
    }

    mpz_t* SieveOfEratosthenes(int size){
        mpz_t* primes = new mpz_t[maxRange];
        for (int i = 0; i <= maxRange; i++){
            mpz_init(primes[i]);
            mpz_set_d(primes[i], 1);
        }

        unsigned long long int p = 0;

        for (int p = 2; p*p <= maxRange; p++){
            if (mpz_cmp_ui(primes[p], 1) == 0){
                for(int i = p*p; i<= maxRange; i += p) 
                    mpz_set_ui(primes[i], 0);
            }
        }

        int j = 0;
        for (int i = 0; i < maxRange; i++){
            if (mpz_cmp_ui(primes[i], 0) != 0){
                j++;
            }
        }

        cout << "PRIMES: " << j << endl;

        mpz_t* holder = new mpz_t[100];
        for (int i = 0; i < j; i++){
            mpz_init(holder[i]);
        }

        j = 0;
        for(int p = 2; p <= maxRange; p++){
            if(mpz_cmp_ui(primes[p], 1) == 0){
                mpz_set_ui(holder[j], p);
                j++;
            }
        }

        return holder;
    }

    // CHECK OK
    mpz_t* customPrime(){
        mpz_t nextPrime;
        mpz_init(nextPrime);

        mpz_nextprime(nextPrime, currPrime);

        mpz_t* holder = new mpz_t[2];
        mpz_init(holder[0]);
        mpz_init(holder[1]);


        for (int i = 0; i < iter; i++){
            mpz_set(holder[0], nextPrime);
            mpz_nextprime(holder[1], holder[0]);
            mpz_set(currPrime, holder[0]);
            mpz_set(nextPrime, holder[1]);
        }

        return holder;
    }
};