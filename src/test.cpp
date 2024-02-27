#include <cstdlib>
#include "complex.h"
#include "transforms.h"
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <cmath>

#define MIN_OFFSET 0.001

using namespace CustomComplex;
using namespace std;


void writeDat(std::vector<Complex> norms){
    ofstream out("output.dat");
    out << "# X - Y" << endl;
    for(int i = 0; i < norms.size(); ++i){
        double sum = 0;
        for(int j = 0;j < norms.size(); ++j)
            sum += norms[j].getMagnitude() * cos(2*M_PI*j*i + norms[j].getPhase());
        out << "  " << i << "   " << sum << endl;
    }
    out.close();
}

double function(double x){
    return x;
}

int main(int argc, char* argv[]){
    std::vector<double> v = std::vector<double>();
    for(int i = 0;i < 40; i++)
        v.push_back(function(i));
    std::vector<Complex> res = Transforms::DFT(v);
    std::vector<Complex> normalized = std::vector<Complex>();

    for(int i = 0;i < v.size();++i){
        double img, re;
        img = std::abs(res[i].getImg()) < MIN_OFFSET ? 0 : res[i].getImg();
        re = std::abs(res[i].getReal()) < MIN_OFFSET ? 0 : res[i].getReal();
        Complex p = Complex::fromCoord(re, img);
        normalized.push_back(Complex::fromPhase(p.getMagnitude()/v.size(), p.getPhase()));
        //std::cout << p << std::endl;
        //std::cout << "AMP : " << (p.getMagnitude())/v.size() << " PHASE : " << p.getPhase() << std::endl;
    }

    writeDat(normalized);
    return 0;
}
