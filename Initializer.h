#include <iostream>
#include <string.h>
#include "CryptoSystem.h"
#include "Miscellaneous.h"

using namespace std;
class Initializer: public PrimeGenerate, PrimeTest, Converter {

private:
    int nextPrimeIter, iter, len, flag, flag2 = 0;
public:

    Initializer(){
    }

    Initializer(int flag, int flag2){
        this->flag = flag;
        this->flag2 = flag2;
    }

    Initializer(string message, int flag): Converter(message){
        len = message.length();
        this->flag = flag;
    }

    Initializer(int iter, mpz_t currPrime1, int flag):PrimeGenerate(currPrime1, iter), PrimeTest(currPrime1){
        this->flag = flag;
        this->flag2 = flag2;
    }

    void initAll(){

        if (flag ==  0){
            mpz_t* primes = customPrime();
            int test = millerRabinsTest();

            if (test){
                RSA rsa(primes);
                rsa.generateKeys();
                rsa.printKeys();
            }
        } else if (flag == 1){

            File f1;
            RSA rsaE;
            mpz_t data, E, N, dataStream1[len], decStream1[len];
            mpz_init(E);
            mpz_init(N);
            cout << "Enter Encryption Key: ";
            gmp_scanf("%Zd", E);
            cout << "Enter N: ";
            gmp_scanf("%Zd", N);

            char* msgChar1 = new char[len];
            msgChar1 = stringToChar();

            for (int i = 0; i < len; i++){
                mpz_init_set_ui(data, msgChar1[i]);
                rsaE.encrypt(data, E, N);
                mpz_init_set(dataStream1[i], data);
                mpz_init(decStream1[i]);
            }

            f1.writeFile(dataStream1, len);  
            
        } else if (flag == 2){

            int lines = 0;
            string l;
            ifstream file("encData.txt");
            while (getline(file, l)){
                lines++;
            }

            File f;
            RSA rsaD;
            mpz_t D, N1, dataStream[lines], decStream[lines];
            mpz_init(D);
            mpz_init(N1);

            cout << "Enter Decryption Key: ";
            gmp_scanf("%Zd", D);
            cout << "Enter N: ";
            gmp_scanf("%Zd", N1);

            for (int i = 0; i < lines; i++){
                mpz_init(decStream[i]);
            }
            f.readFile(decStream, lines);

            for (int i = 0; i < lines; i++){
                rsaD.decrypt(decStream[i], D, N1);
            }
            if (flag2 == 0){
                string s = mpzToChar(decStream, lines);
                Converter c;
                c.base64ToImage(s);
            } else {
                string s = mpzToChar(decStream, lines);
                cout << s << endl;
            }

        } else {
            cout << "Something went wrong :(" << endl;
        }
    }
    void friend menu1();
    void friend menu2();
};

void menu1(){
    cout << "Press G for generating keys, ";
    cout << "Press E for encrypting a new message, ";
    cout << "Press D for decrypting a cipher: ";
}

void menu2(){
    cout << "Enter I for Image, ";
    cout << "Enter M for Message: ";
}