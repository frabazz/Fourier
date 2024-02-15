#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

typedef struct complex{
    double re;
    double img;
} complex_t;

typedef struct kcos{
    double coeff;
    double freq;
}kcos_t;

vector<complex_t> dft(vector<double> samples){
    vector<complex_t> res = vector<complex_t>();
    float sumRE = 0, sumIMG = 0;
    for(int k = 0; k < samples.size(); ++k){
        for(int n = 0; n < samples.size(); ++n){
            double angle = -(2*M_PI*k*n)/samples.size();
            sumRE  += samples[n] * cos(angle);
            sumIMG += samples[n] * sin(angle);
        }
        res.push_back({sumRE, sumIMG});
    }

    return res;
}
//https://dsp.stackexchange.com/questions/38885/the-number-of-sine-and-cosine-waves-in-an-n-point-dft

vector<freq_t> dftV2(vector<double> samples){
    vector<freq_t> res = vector<freq_t>();

}


int main(int argc, char* argv[]){
    vector<double> samples = {1, 2, 3, 1, 2, 3};
    vector<complex_t> ris = dft(samples);

    for(int i = 0;i < ris.size(); ++i){
        printf("%f*cos((2*%d*\\pi*x))/%d+", 2*ris[i].re, i, int(samples.size()));
        printf("%f*sin(2*%d*\\pi*x)/%d+", -2*ris[i].img, i, int(samples.size()));
    }
    cout << endl;
    return 0;
}
