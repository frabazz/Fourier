#include "wave.h"
#include <iostream>
#include <string>
#include <array>
#include <iomanip>
#include <fstream>

#define FLOAT_PRECISION 4
#define SPACES 10

using namespace std;
using namespace Wave;

string column1 = "index";
string column2 = "value";

void initDat(ofstream* out){
    (*out) << column1;
    for(int i = 0;i < SPACES;i++) (*out) << " ";
    (*out) << column2 << endl;
}

void printCouple(ofstream* out, double d1, double d2){
    (*out) << fixed << setprecision(FLOAT_PRECISION) << d1;
    int spaces = column1.length() - FLOAT_PRECISION + SPACES;
    for(int i = 0;i < spaces;i++) (*out) << " ";
    (*out) << fixed << setprecision(FLOAT_PRECISION) << d2 << endl;
}

int main(int argc, char* argv[]){

    if(argc < 2){
        cout << "not enough arguments" << endl;
        return 0;
    }

    WaveFile file = WaveFile(argv[1]);
    if(file.open()){
        file.printInfo();
        ofstream output = new ofstream("output.dat", "w");
        cout << "DATA values: " << endl;
        vector<double> sample = vector<double>(file.subChunk1.numChannels);

        for(int i = 0; i < 100; i++){
            file >> &sample;
            for(double s : sample)
                cout << s << endl;
        }

    }
    else
        cout << "error opening file" << endl;

}
