#define MIN_OFFSET 0.001

#include "complex.h"
#include "transforms.h"
#include <vector>
#include <cmath>


using namespace CustomComplex;

int main(int argc, char* argv[]){
    std::vector<double> v = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<Complex> res = Transforms::DFT(v);
    std::cout << "RESULTS: " << std::endl;
    for(int i = 0;i < v.size()/2;++i){
        double img, re;
        img = std::abs(res[i].getImg()) < MIN_OFFSET ? 0 : res[i].getImg();
        re = std::abs(res[i].getReal()) < MIN_OFFSET ? 0 : res[i].getReal();
        Complex p = Complex::fromCoord(re, img);
        //std::cout << p << std::endl;
        std::cout << "AMP : " << (p.getMagnitude()*2)/v.size() << " PHASE : " << p.getPhase() << std::endl;
    }
    return 0;
}
