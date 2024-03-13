#include <cstdlib>
#include "complex.h"
#include "transforms.h"
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <cmath>

#define MIN_OFFSET 0.0000000001
#define DELTA 0.01

typedef long double ld;

using namespace CustomComplex;
using namespace std;



ld calcFourier(vector<Complex> DFT, double x){
    Complex r = Complex::fromCoord(0, 0);
    for(int i = 0; i < DFT.size(); ++i)
        r = r + DFT[i]*Complex::fromPhase(1, (2*M_PI*i*x)/DFT.size());

    return (r.getReal()/DFT.size());
}

void writeDat(std::vector<Complex> DFT, double size){
    ofstream out("output.dat");
    out << "# X - Y" << endl;
    ld x = 0;
    while(x < size){
        ld ris = calcFourier(DFT, x);
        out << " " << x << "   " << calcFourier(DFT, x) << std::endl;
        x += DELTA;
    }
    out.close();
}
double function(double x){
    return x;
}

int main(int argc, char* argv[]){
    std::vector<ld> v = std::vector<ld>();
    int rounds = 50;
    for(int i = 0;i < rounds;i++)
        v.push_back((i - rounds/2.0) * (i - rounds/2.0));
    std::vector<Complex> res = Transforms::DFT(v);
    std::cout << "DFT VALUES: " << std::endl;
    for(auto r : res)
        std::cout << r << std::endl;
    writeDat(res, 200);
    std::system("../src/plot.sh");
    return 0;
}
