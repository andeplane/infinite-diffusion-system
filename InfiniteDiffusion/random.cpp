#include "random.h"
#include <cmath>
Random::Random(long seed) {
   *idum = seed;
    iy = 0;
}

bool Random::nextBool()
{
    return nextDouble()>0.5;
}

int Random::nextInt(const int min, const int max)
{
    return min + (max-min+1)*nextDouble();
}

double Random::nextGauss(double mean, double standardDeviation) {

  return mean +( sqrt( -2.0*log(1.0 - nextDouble()) )
                 * cos( 6.283185307 * nextDouble() ) ) * standardDeviation;
}

QVector3D Random::nextQVector3D()
{
    double x = nextDouble();
    double y = nextDouble();
    double z = nextDouble();
    return QVector3D(x,y,z);
}

double Random::nextDouble()
{
   int             j;
   long            k;
   double          temp;

   if (*idum <= 0 || !iy) {
      if (-(*idum) < 1) *idum=1;
      else *idum = -(*idum);
      for(j = NTAB + 7; j >= 0; j--) {
         k     = (*idum)/IQ;
         *idum = IA*(*idum - k*IQ) - IR*k;
         if(*idum < 0) *idum += IM;
         if(j < NTAB) iv[j] = *idum;
      }
      iy = iv[0];
   }
   k     = (*idum)/IQ;
   *idum = IA*(*idum - k*IQ) - IR*k;
   if(*idum < 0) *idum += IM;
   j     = iy/NDIV;
   iy    = iv[j];
   iv[j] = *idum;
   if((temp=AM*iy) > RNMX) return RNMX;
   else return temp;
}
