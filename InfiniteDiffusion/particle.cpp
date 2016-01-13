#include "particle.h"

Particle::Particle()
{

}

QVector3D Particle::position() const
{
    return m_position;
}

void Particle::setPosition(const QVector3D &position)
{
    m_position = position;
}

QVector3D &Particle::position()
{
    return m_position;
}

bool Particle::active() const
{
    return m_active;
}

void Particle::setActive(bool active) {
    m_active = active;
}


