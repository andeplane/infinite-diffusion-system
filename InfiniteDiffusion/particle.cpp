#include "particle.h"

QVector3D Particle::positionUnwrapped() const
{
    return m_positionUnwrapped;
}

void Particle::setPositionUnwrapped(const QVector3D &positionUnwrapped)
{
    m_positionUnwrapped = positionUnwrapped;
}

Particle::Particle()
{

}

void Particle::addPosition(const QVector3D &delta)
{
    m_position[0] += delta[0];
    m_position[1] += delta[1];
    m_position[2] += delta[2];

    m_positionUnwrapped[0] += delta[0];
    m_positionUnwrapped[1] += delta[1];
    m_positionUnwrapped[2] += delta[2];
}

void Particle::addPositionComponent(int dimension, float delta)
{
    m_position[dimension] += delta;
    m_positionUnwrapped[dimension] += delta;
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


