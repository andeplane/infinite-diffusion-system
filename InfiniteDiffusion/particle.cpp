#include "particle.h"

QVector3D Particle::originalPosition() const
{
    return m_originalPosition;
}

void Particle::setOriginalPosition(const QVector3D &originalPosition)
{
    m_originalPosition = originalPosition;
}

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


