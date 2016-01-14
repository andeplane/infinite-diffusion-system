#ifndef VOIDGEOMETRY_H
#define VOIDGEOMETRY_H
#include "geometry.h"

class VoidGeometry : public Geometry
{
public:
    VoidGeometry();

    // Geometry interface
public:
    virtual bool pointIsVoid(const float &x, const float &y, const float &z);
};

#endif // VOIDGEOMETRY_H
