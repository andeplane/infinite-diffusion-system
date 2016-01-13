#pragma once
#include "geometry.h"
class CylinderGeometry : public Geometry
{
    Q_OBJECT
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)
private:
    float m_radius = 1.0;
public:
    CylinderGeometry();

    virtual bool pointIsVoid(const float &x, const float &y, const float &z);
    float radius() const;
public slots:
    void setRadius(float radius);
signals:
    void radiusChanged(float radius);
};
