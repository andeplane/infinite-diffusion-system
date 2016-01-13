#include "cylindergeometry.h"

CylinderGeometry::CylinderGeometry()
{

}

bool CylinderGeometry::pointIsVoid(const float &x, const float &y, const float &z)
{
    float dr2 = x*x + y*y;
    return dr2<(m_radius*m_radius);
}

float CylinderGeometry::radius() const
{
    return m_radius;
}

void CylinderGeometry::setRadius(float radius)
{
    if (m_radius == radius)
        return;

    m_radius = radius;
    emit radiusChanged(radius);
}
