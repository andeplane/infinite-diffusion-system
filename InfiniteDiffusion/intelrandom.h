#ifndef INTELRANDOM_H
#define INTELRANDOM_H
#ifdef __INTEL_COMPILER
#include <mkl.h>
#include <vector>

class IntelRandom
{
private:
    VSLStreamStatePtr m_stream;
    std::vector<float> m_floats;
    std::vector<double> m_doubles;
    std::vector<int> m_int;
    std::vector<int> m_uint;

public:
    // Parameter is described in https://software.intel.com/en-us/node/521847#TBL10-2
    IntelRandom(MKL_UINT seed = 777, MKL_UINT parameter = VSL_BRNG_SFMT19937);
};
#endif
#endif // INTELRANDOM_H
