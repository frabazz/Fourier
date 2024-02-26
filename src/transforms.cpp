#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>

#include "transforms.h"
#include "complex.h"


using namespace CustomComplex;
std::vector<Complex> Transforms::DFT(std::vector<double> samples){
    int N = samples.size();
    std::vector<Complex> res = std::vector<Complex>();
    for(int k = 0; k < N; ++k){
        Complex c = Complex::fromPhase(0, 0);
        for(int n = 0; n < N; ++n){
            double exp = -(((2*M_PI*k*n)/N));
            c = c + Complex::fromPhase(samples[n], exp);
        }

        res.push_back(c);
    }

    return res;
}
