#include <cstdlib>
#include "complex.h"
#include "transforms.h"
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <cmath>

#define MIN_OFFSET 0.001
#define DELTA 0.01

using namespace CustomComplex;
using namespace std;



double calcFourier(vector<Complex> DFT, double x){
    Complex r = Complex::fromCoord(0, 0);
    for(int i = 0; i < DFT.size(); ++i)
        r = r + DFT[i]*Complex::fromPhase(1, (2*M_PI*i*x)/DFT.size());

    return (1.0/DFT.size()) * r.getReal();
}

void writeDat(std::vector<Complex> DFT, double size){
    ofstream out("output.dat");
    out << "# X - Y" << endl;
    double x = 0;
    while(x < size){
        out << " " << x << "   " << calcFourier(DFT, x) << std::endl;
        x += DELTA;
    }
    out.close();
}
double function(double x){
    return x;
}

int main(int argc, char* argv[]){
    std::vector<double> v = {1, 2, 3, 4, 3, 2, 1};
    std::vector<Complex> res = {
        Complex::fromCoord(10, 0),
        Complex::fromCoord(-2, 2),
        Complex::fromCoord(-2, 0),
        Complex::fromCoord(-2, -2)
    };
    std::cout << "DFT VALUES: " << std::endl;
    for(auto r : res)
        std::cout << r << std::endl;
    writeDat(res, 10);
    return 0;
}
