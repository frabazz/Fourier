#include <vector>
#include "complex.h"
#ifndef FTRANSFORMS
#define FTRANSFORMS

typedef long double ld;

namespace Transforms{
    std::vector<CustomComplex::Complex> DFT(std::vector<ld>);
}

#endif
