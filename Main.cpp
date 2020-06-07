#include <iostream>
#include <string>
#include "Initializer.h"
#include <stdio.h>

using namespace std;
#define LOG(x) cout << x << endl

int main(){

    int iterations = 10;
    mpz_t initPrime;
    mpz_init_set_str(initPrime, "32317006071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338476170470581645852036305042887575891541065808607552399123930385521914333389668342420684974786564569494856176035326322058077805659331026192708460314150258592864177116725943603718461857357598351152334063994785580370721665417662212881203104945914551140008147396357886767669820042828793708588252247031092071155540224751031064253209884099238184688246467489498721336450133890847543", 10);

    char choice;
    menu1();
    cin >> choice;

    if (choice == 'G' || choice == 'g'){
        Initializer keys(iterations, initPrime, 0);
        keys.initAll();
    } else if (choice == 'E' || choice == 'e'){
        char ch;
        menu2();
        cin >> ch;
        if (ch == 'I' || ch == 'i'){
            string image;
            
            Converter c("1.png");
            image = c.imageToBase64();
            Initializer initEnc(image, 1);
            initEnc.initAll();
        } else {
            string msg;
            cout << "Enter a Message: ";
            getline(cin >> ws, msg);
            Initializer initEnc(msg, 1);
            initEnc.initAll();
        }

    } else if (choice == 'D' || choice == 'd'){
        char ch;
        menu2();
        cin >> ch;
        if (ch == 'I' || ch == 'i'){
            string image;
            Initializer initDec(2, 0);
            initDec.initAll();
        } else {
            Initializer initDec(2, 1);
            initDec.initAll();
        }
    }
}