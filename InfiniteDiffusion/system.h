#pragma once

#include <QObject>
#include <QVector>
#include "particle.h"
#include "geometry/geometry.h"

class System : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Geometry* geometry READ geometry WRITE setGeometry NOTIFY geometryChanged)
private:
    QVector<Particle> m_particles;
    Geometry *m_geometry = nullptr;

public:
    System();
    void tick();

    // Getters and setters
    QVector<Particle> &particles() { return m_particles; }
    Geometry *geometry() { return m_geometry; }

public slots:
    void setGeometry(Geometry* geometry);
signals:
    void geometryChanged(Geometry* geometry);
};
