#pragma once

#include <QObject>
#include <QVector>
#include <QVariantList>
#include "statistics/statistics.h"
#include "particle.h"
#include "GeometryLibrary/misc/random.h"
#include "GeometryLibrary/models/models.h"
class SystemProperties : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Model* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(float stepLength READ stepLength WRITE setStepLength NOTIFY stepLengthChanged)
    Q_PROPERTY(float dt READ dt WRITE setDt NOTIFY dtChanged)
    Q_PROPERTY(bool willReset READ willReset WRITE setWillReset NOTIFY willResetChanged)
    Q_PROPERTY(int numberOfParticles READ numberOfParticles WRITE setNumberOfParticles NOTIFY numberOfParticlesChanged)
    Q_PROPERTY(int posMin READ posMin WRITE setPosMin NOTIFY posMinChanged)
    Q_PROPERTY(int posMax READ posMax WRITE setPosMax NOTIFY posMaxChanged)
    Q_PROPERTY(bool periodic READ periodic WRITE setPeriodic NOTIFY periodicChanged)
private:

    Model* m_model = nullptr;
    float m_stepLength = 0.0;
    bool m_willReset = false;
    int m_numberOfParticles = 100000;
    int m_posMin = -100;
    int m_posMax = 100;
    float m_dt = 1;
    bool m_periodic = true;

public:
    float stepLength() const;
    bool willReset() const;
    int numberOfParticles() const;
    int posMin() const;
    int posMax() const;
    float dt() const;

    Model* model() const;

public slots:
    void setStepLength(float stepLength);
    void setWillReset(bool willReset);
    void setNumberOfParticles(int numberOfParticles);
    void setPosMin(int posMin);
    void setPosMax(int posMax);
    void setDt(float dt);
    void setModel(Model* model);

    void setPeriodic(bool periodic);

signals:
    void stepLengthChanged(float stepLength);
    void willResetChanged(bool willReset);
    void numberOfParticlesChanged(int numberOfParticles);
    void posMinChanged(int posMin);
    void posMaxChanged(int posMax);
    void dtChanged(float dt);
    void modelChanged(Model* model);

    void periodicChanged(bool periodic);

public:
friend class System;
bool periodic() const;
};

class System : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SystemProperties* properties READ properties WRITE setProperties NOTIFY propertiesChanged)
    Q_PROPERTY(float time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QVariantList statistics READ statistics WRITE setStatistics NOTIFY statisticsChanged)
private:
    QVector<Particle> m_particles;
    SystemProperties* m_properties = nullptr;
    Random m_random;
    float m_time = 0;
    QVariantList m_statistics;
    void applyPeriodic(QVector3D &position);

public:
    System();
    bool tick();
    Q_INVOKABLE void createParticles(int numberOfParticles, float from, float to);

    // Getters and setters
    QVector<Particle> &particles() { return m_particles; }
    SystemProperties* properties() const;
    QVector<QVector3D> particlePositions();
    float time() const;
    QVariantList statistics() const;

public slots:
    void setProperties(SystemProperties* properties);
    void setTime(float time);
    void setStatistics(QVariantList statistics);

signals:
    void propertiesChanged(SystemProperties* properties);
    void timeChanged(float time);
    void statisticsChanged(QVariantList statistics);
};
