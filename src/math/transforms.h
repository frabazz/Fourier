#include "complex.h"
#include <complex>
#include <vector>
#ifndef FTRANSFORMS
#define FTRANSFORMS

typedef long double ld;

namespace Transforms {
std::vector<CustomComplex::Complex> DFT(std::vector<ld>);
std::vector<std::complex<double>> FFT(std::vector<double>);

} // namespace Transforms

#endif
