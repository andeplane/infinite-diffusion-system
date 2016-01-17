#include "system.h"
#include <QDebug>
#ifdef __INTEL_COMPILER

#include <mkl.h>
#include <mkl_vsl.h>

#endif
System::System()
{
#ifdef __INTEL_COMPILER
    vslNewStream( &m_intelRandomStream, VSL_BRNG_SFMT19937, 777);
#endif
}

void System::tick()
{
    if(!m_properties->geometry()) return;
#ifdef __INTEL_COMPILER
    int numberOfParticles = m_positions.size();
    m_randomFloats.resize(numberOfParticles);
    m_randomInts.resize(numberOfParticles);
    viRngUniform(VSL_RNG_METHOD_UNIFORM_STD, m_intelRandomStream, numberOfParticles, &m_randomInts.front(), 0, 2);
    vsRngUniform(VSL_RNG_METHOD_UNIFORM_STD, m_intelRandomStream, numberOfParticles, &m_randomFloats.front(), -m_properties->stepLength(), m_properties->stepLength());
#pragma simd
    for(int i=0; i<numberOfParticles; i++) {
        const int moveDimension = m_randomInts[i];
        const float step = m_randomFloats[i];
        m_positions[i][moveDimension] += step;
        if(!m_properties->m_geometry->pointIsVoid(m_positions[i])) {
            // Reject. We collided with a wall
            m_positions[i][moveDimension] -= step;
        }
    }
#else
    for(Particle &particle : m_particles) {
        int moveDimension = m_random.nextInt(0,2);
        double step = (1.0 - 2.0*m_random.nextBool())*m_properties->stepLength();
        particle[moveDimension] += step;
        if(!m_properties->m_geometry->pointIsVoid(particle.position())) {
            // Reject. We collided with a wall
            particle[moveDimension] -= step;
        }
    }
#endif
}

SystemProperties *System::properties() const
{
    return m_properties;
}

QVector<QVector3D> System::particlePositions()
{
#ifdef __INTEL_COMPILER
    return m_positions;
#else
    QVector<QVector3D> positions;
    positions.reserve(m_particles.size());
    for(Particle &particle : m_particles) {
        positions.push_back(particle.position());
    }
    return positions;
#endif
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
#ifdef __INTEL_COMPILER
    m_positions.resize(numberOfParticles);
    m_originalPositions.resize(numberOfParticles);
    for(int i=0; i<numberOfParticles; i++) {
        QVector3D &position = m_positions[i];
        bool isInVoid = false;
        while(!isInVoid) {
            position = m_random.nextQVector3D(from,to);
            m_originalPositions[i] = position;
            isInVoid = m_properties->m_geometry->pointIsVoid(position);
        }
    }
#else
    m_particles.resize(numberOfParticles);
    for(Particle &particle : m_particles) {
        bool isInVoid = false;
        while(!isInVoid) {
            particle.setPosition(m_random.nextQVector3D(from,to));
            particle.setOriginalPosition(particle.position());
            isInVoid = m_properties->m_geometry->pointIsVoid(particle.position());
        }
    }
#endif
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
