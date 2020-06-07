#include <iostream>
#include <string.h>
#include "base64.h"
#include <fstream>
#include <sstream>

using namespace std;
class Converter {
private:
    string data;
public:
    Converter(){
        
    }

    Converter(string data){
        this-> data = data;
    }

    char* stringToChar(){
        int l = data.length();
        char* arr = new char[l];

        strcpy(arr, data.c_str());
        
        return arr;
    }

    string mpzToChar(mpz_t data1[], int size){
        cout << "Decrypted Message: ";
        char* da = new char[size];
        for (int i = 0; i < size; i++){
            da[i] = (char) mpz_get_ui(data1[i]);
        }
        string s(da);
        // cout << s << endl;
        return s;
    }

    string imageToBase64(){
        ifstream file{data};
  
        string const file_contents = static_cast<std::ostringstream&>
        (ostringstream{} << file.rdbuf()).str();

        string encoded = base64_encode(file_contents, file_contents.length());
        return encoded;
    }

    void base64ToImage(string base64){
        string decoded = base64_decode(base64, false);
        std::ofstream out("GeneratedImage.png");
        out << decoded;
        out.close();
    }
};

class File {

private:
public:

    void writeFile(mpz_t data[], int size){
        FILE* file;
        file = fopen("encData.txt", "w");

        for (int i = 0; i < size; i++){
            mpz_out_str(file, 10, data[i]);
            fputc(10, file);
        }

        fclose(file);
    }

    void readFile(mpz_t data[], int size){

        FILE* file;
        file = fopen("encData.txt", "r");

        for (int i = 0; i < size; i++){
            mpz_init(data[i]);
            mpz_inp_str(data[i], file, 10);
        }
        fclose(file);   
    }
};
