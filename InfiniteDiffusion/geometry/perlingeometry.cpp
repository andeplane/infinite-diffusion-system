#include "perlingeometry.h"

PerlinGeometry::PerlinGeometry()
{

}

bool PerlinGeometry::pointIsVoid(const float &x, const float &y, const float &z)
{

}


int PerlinProperties::octaves() const
{
    return m_octaves;
}

float PerlinProperties::persistence() const
{
    return m_persistence;
}

float PerlinProperties::sharpness() const
{
    return m_sharpness;
}

bool PerlinProperties::abs() const
{
    return m_abs;
}

bool PerlinProperties::invert() const
{
    return m_invert;
}

void PerlinProperties::setOctaves(int octaves)
{
    if (m_octaves == octaves)
        return;

    m_octaves = octaves;
    emit octavesChanged(octaves);
}

void PerlinProperties::setPersistence(float persistence)
{
    if (m_persistence == persistence)
        return;

    m_persistence = persistence;
    emit persistenceChanged(persistence);
}

void PerlinProperties::setSharpness(float sharpness)
{
    if (m_sharpness == sharpness)
        return;

    m_sharpness = sharpness;
    emit sharpnessChanged(sharpness);
}

void PerlinProperties::setAbs(bool abs)
{
    if (m_abs == abs)
        return;

    m_abs = abs;
    emit absChanged(abs);
}

void PerlinProperties::setInvert(bool invert)
{
    if (m_invert == invert)
        return;

    m_invert = invert;
    emit invertChanged(invert);
}
