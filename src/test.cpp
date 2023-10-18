#include "wave.h"
#include <iostream>

using namespace std;
using namespace Wave;

int main(int argc, char* argv[]){

    if(argc < 2){
        cout << "not enough arguments" << endl;
        return 0;
    }

    WaveFile file = WaveFile(argv[1]);
    if(file.open())
        file.printInfo();
    else
        cout << "error opening file" << endl;
}
