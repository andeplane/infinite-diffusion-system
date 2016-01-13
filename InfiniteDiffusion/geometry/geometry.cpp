#include "geometry.h"

Geometry::Geometry()
{

}

bool Geometry::pointIsVoid(const QVector3D &point)
{
    return pointIsVoid(point[0],point[1],point[2]);
}
