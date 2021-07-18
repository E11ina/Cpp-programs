//Converter
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;
const string usg = "usage";

string itoBase(unsigned int nb, string base);
string itoBase(string nb, string baseSrc, string baseDst);

int main(int argc, char *argv[])
{
    bool tCorrect = true;
    for (int i = 1; i < argc; i++) {
        if (!atoi(argv[i])) {
            tCorrect = false;
            cout << usg;
            break;
        }
    }

    if (tCorrect) {
        switch (argc) {
            case 3: {
                cout << itoBase(atoi(argv[1]), (string)argv[2]);
                break;
            }
            case 4: {
                cout << itoBase((string)argv[1], (string)argv[2],
                        (string)argv[3]);
                break;
            }
            default: {
                cout << usg;
                break;
            }
        }
    }

    return 0;
}

string itoBase(unsigned int nb, string base) {

    int num_base = atoi(base.c_str());
    int tCnt = 1;
    int quot = nb;
    do {
        quot /= num_base;
        tCnt++;
    } while (quot >= num_base);

    string sourceNumber = "";
    char mass[tCnt];

    itoa(nb, mass, num_base);

    for (int i = 0; i < tCnt; i++) {
        sourceNumber += mass[i];
    }

    return sourceNumber;
}

string itoBase(string nb, string baseSrc, string baseDst) {

    int tNum = atoi(nb.c_str()); 
    int base_num = atoi(baseSrc.c_str());

    
    int numTen;
    if (base_num != 10) {
        int rest;
        int itr = 0;
        numTen = 0;
        do {
            rest = tNum % 10;
            numTen += rest * pow(base_num, itr++);
            tNum /= 10;
        } while (tNum);
    } else {
        numTen = tNum;
    }

    return itoBase(numTen, baseDst);
}
