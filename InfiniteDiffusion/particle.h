#pragma once
#include <QVector3D>

class Particle
{
private:
    QVector3D m_originalPosition;
    QVector3D m_position;
    bool m_active;

public:
    Particle();
    float &operator [](const int &index) { return m_position[index]; }

    // Getters and setters
    bool active() const;
    void setActive(bool active);
    QVector3D &position();
    QVector3D position() const;
    void setPosition(const QVector3D &position);
    QVector3D originalPosition() const;
    void setOriginalPosition(const QVector3D &originalPosition);
};