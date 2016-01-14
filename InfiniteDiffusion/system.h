#pragma once

#include <QObject>
#include <QVector>
#include "particle.h"
#include "random.h"
#include "geometry/geometry.h"

class SystemProperties : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Geometry* geometry READ geometry WRITE setGeometry NOTIFY geometryChanged)
    Q_PROPERTY(float stepLength READ stepLength WRITE setStepLength NOTIFY stepLengthChanged)
private:

    Geometry* m_geometry = nullptr;
    float m_stepLength = 0.0;

public:
    Geometry* geometry() const;
    float stepLength() const;

public slots:
    void setGeometry(Geometry* geometry);
    void setStepLength(float stepLength);

signals:
    void geometryChanged(Geometry* geometry);
    void stepLengthChanged(float stepLength);
    friend class System;
};

class System : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SystemProperties* properties READ properties WRITE setProperties NOTIFY propertiesChanged)
private:
    QVector<Particle> m_particles;
    SystemProperties* m_properties = nullptr;
    Random m_random;

public:
    System();
    void tick();
    Q_INVOKABLE void createParticles(int numberOfParticles, float from, float to);

    // Getters and setters
    QVector<Particle> &particles() { return m_particles; }
    SystemProperties* properties() const;
    QVector<QVector3D> particlePositions();

public slots:
    void setProperties(SystemProperties* properties);

signals:
    void propertiesChanged(SystemProperties* properties);
};
