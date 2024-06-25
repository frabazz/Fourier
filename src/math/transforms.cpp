
#define _USE_MATH_DEFINES
#define MIN_DOUBLE 0.0000000000001

#include <cmath>
#include <vector>
#include <iostream>

#include "transforms.h"
#include "complex.h"
#include <complex>

typedef long double ld;

std::vector<CustomComplex::Complex> Transforms::DFT(std::vector<ld> samples){
    int N = samples.size();
    std::vector<CustomComplex::Complex> res = std::vector<CustomComplex::Complex>();
    for(int k = 0; k < N; ++k){
      CustomComplex::Complex c = CustomComplex::Complex::fromPhase(0, 0);
        for(int n = 0; n < N; ++n){
            ld exp = -(((2*M_PI*k*n)/N));
	    CustomComplex::Complex nth = CustomComplex::Complex::fromPhase(samples[n], exp);
            c = c + nth;
        }
        ld real = c.getReal(), img = c.getImg();

        res.push_back(CustomComplex::Complex::fromCoord(
            std::abs(real) < MIN_DOUBLE ? 0 : real,
            std::abs(img) < MIN_DOUBLE ? 0 : img
        ));
    }

    return res;
}

std::vector<std::complex<double>> Transforms::FFT(std::vector<double>){
  
} 
