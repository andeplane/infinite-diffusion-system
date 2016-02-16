#pragma once
#include <QObject>
#include "geometry.h"

class PerlinProperties : public QObject {
    Q_OBJECT
    Q_PROPERTY(int octaves READ octaves WRITE setOctaves NOTIFY octavesChanged)
    Q_PROPERTY(float persistence READ persistence WRITE setPersistence NOTIFY persistenceChanged)
    Q_PROPERTY(float sharpness READ sharpness WRITE setSharpness NOTIFY sharpnessChanged)
    Q_PROPERTY(bool abs READ abs WRITE setAbs NOTIFY absChanged)
    Q_PROPERTY(bool invert READ invert WRITE setInvert NOTIFY invertChanged)
private:
    int m_octaves = 1;
    float m_persistence = 1.0;
    float m_sharpness = 1.0;
    bool m_abs = false;
    bool m_invert = false;

public:
    int octaves() const;
    float persistence() const;
    float sharpness() const;
    bool abs() const;
    bool invert() const;

public slots:
    void setOctaves(int octaves);
    void setPersistence(float persistence);
    void setSharpness(float sharpness);
    void setAbs(bool abs);
    void setInvert(bool invert);

signals:
    void octavesChanged(int octaves);
    void persistenceChanged(float persistence);
    void sharpnessChanged(float sharpness);
    void absChanged(bool abs);
    void invertChanged(bool invert);
};

class PerlinGeometry : public Geometry
{
    Q_OBJECT
    Q_PROPERTY(PerlinProperties* properties READ properties WRITE setProperties NOTIFY propertiesChanged)
private:

    PerlinProperties* m_properties = nullptr;
    RegularParameters m_noiseParameters;
    GeometryLibrary m_geometry;
    bool m_initialized = false;
    void Initialize();

public:

    PerlinGeometry();
    bool pointIsVoid(const float &x, const float &y, const float &z);
    PerlinProperties* properties() const
    {
        return m_properties;
    }
public slots:
    void setProperties(PerlinProperties* properties)
    {
        if (m_properties == properties)
            return;

        m_properties = properties;
        emit propertiesChanged(properties);
    }
signals:
    void propertiesChanged(PerlinProperties* properties);
};
