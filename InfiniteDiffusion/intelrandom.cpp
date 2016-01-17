#ifdef __INTEL_COMPILER
#include "intelrandom.h"

IntelRandom::IntelRandom(MKL_UINT seed, MKL_UINT parameter)
{
    vslNewStream( &m_stream, parameter, seed);
}
#endif
