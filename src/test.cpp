#include "complex.h"
#include "transforms.h"
#include <vector>

using namespace CustomComplex;

int main(int argc, char* argv[]){
    std::vector<double> v = {0, 0.707, 1, 0.707, 0, -0.707, -1, -0.707};
    std::vector<Complex> res = Transforms::DFT(v);

    for(auto c : res)
        std::cout << c << std::endl;
    return 0;
}
