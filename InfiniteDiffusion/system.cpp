#include "system.h"
#include <QDebug>

System::System()
{

}

void System::tick()
{
    if(!m_properties->geometry()) return;
    for(Particle &particle : m_particles) {
        int moveDimension = m_random.nextInt(0,2);
        double step = (1.0 - 2.0*m_random.nextBool())*m_properties->stepLength();
        particle[moveDimension] += step;
        if(!m_properties->m_geometry->pointIsVoid(particle.position())) {
            // Reject. We collided with a wall
            particle[moveDimension] -= step;
        }
    }
}

SystemProperties *System::properties() const
{
    return m_properties;
}

QVector<QVector3D> System::particlePositions()
{
    QVector<QVector3D> positions;
    positions.reserve(m_particles.size());
    for(Particle &particle : m_particles) {
        positions.push_back(particle.position());
    }
    return positions;
}

void System::setProperties(SystemProperties *properties)
{
    if (m_properties == properties)
        return;

    m_properties = properties;
    emit propertiesChanged(properties);
}

Geometry *SystemProperties::geometry() const
{
    return m_geometry;
}

float SystemProperties::stepLength() const
{
    return m_stepLength;
}

void System::createParticles(int numberOfParticles, float from, float to)
{
    if(!m_properties) return;
    m_particles.resize(numberOfParticles);
    qDebug() << "Creating particles...";
    for(Particle &particle : m_particles) {
        bool isInVoid = false;
        while(!isInVoid) {
            particle.setPosition(m_random.nextQVector3D(from,to));
            isInVoid = m_properties->m_geometry->pointIsVoid(particle.position());
        }
    }
    qDebug() << "Done.";
}

void SystemProperties::setGeometry(Geometry *geometry)
{
    if (m_geometry == geometry)
        return;

    m_geometry = geometry;
    emit geometryChanged(geometry);
}

void SystemProperties::setStepLength(float stepLength)
{
    if (m_stepLength == stepLength)
        return;

    m_stepLength = stepLength;
    emit stepLengthChanged(stepLength);
}
