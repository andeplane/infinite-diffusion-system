#pragma once
#include <QVector3D>

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

class Random {
public:
    long     iy;
    long     iv[NTAB];
    long     idum[1];

    Random(long seed = -1);
    bool nextBool();
    int nextInt(const int min, const int max);
    double nextDouble();
    double nextGauss(double mean = 0.0, double standardDeviation = 1.0);
    QVector3D nextQVector3D();
};
