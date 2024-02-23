#include "complex.h"
#include <iostream>
#include <string>
#include <array>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace CustomComplex;

/*
#define FLOAT_PRECISION 4
#define SPACES 10

using namespace std;
using namespace Wave;

typedef vector<vector<double>> vsample;

int main(int argc, char* argv[]){

    if(argc < 2){
        cout << "not enough arguments" << endl;
        return 0;
    }

    WaveFile file = WaveFile(argv[1]);
    if(file.open()){
        file.printInfo();
        vsample samples = vsample();
        for(int i = 0; i < 150; ++i){
            auto s = vector<double>();
            file >> &s;
            samples.push_back(s);
        }

        cout << "SAMPLES: " << endl;

        for(auto s : samples){
            if(!s.empty())
                cout << s [0] << endl;
        }
    }
    else
        cout << "error opening file" << endl;
}
*/

int main(int argc, char* argv[]){
    Complex c = Complex::fromPhase(4, 3.14/2);
    std::cout << c;

}
