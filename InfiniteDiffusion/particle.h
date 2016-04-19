#pragma once
#include <QVector3D>

class Particle
{
private:
    QVector3D m_positionUnwrapped;
    QVector3D m_position;
    bool m_active;

public:
    Particle();
    void addPosition(const QVector3D &delta);
    void addPositionComponent(int dimension, float delta);
    // Getters and setters
    bool active() const;
    void setActive(bool active);
    QVector3D &position();
    QVector3D mirroredPosition(QVector3D systemSize);
    void setPosition(const QVector3D &position);
    QVector3D positionUnwrapped() const;
    void setPositionUnwrapped(const QVector3D &positionUnwrapped);
};
