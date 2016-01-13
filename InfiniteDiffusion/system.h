#pragma once

#include <QVector>
#include "particle.h"
#include "perlingeometry.h"

class System
{
private:
    QVector<Particle> m_particles;
    PerlinGeometry m_geometry;

public:
    System();
    void tick();

    // Getters and setters
    QVector<Particle> &particles() { return m_particles; }
    PerlinGeometry &geometry() { return m_geometry; }

};
