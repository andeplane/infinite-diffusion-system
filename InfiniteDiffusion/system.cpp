#include "system.h"
#include <QDebug>

System::System()
{

}

bool System::tick()
{
    if(!m_properties->model()) return false;

    if(m_properties->willReset()) {
        m_properties->model()->start();
        m_properties->setWillReset(false);
        m_time = 0;
        createParticles(m_properties->numberOfParticles(), m_properties->posMin(), m_properties->posMax());

        for(QVariant &obj : m_statistics) {
            Statistic *statistic = obj.value<Statistic*>();
            statistic->reset();
            statistic->tick(this);
        }

        m_properties->model()->stop();
        return false;
    }

    Model *currentModel = m_properties->model();
    currentModel->start();
    for(Particle &particle : m_particles) {
        int moveDimension = m_random.nextInt(0,2);
        double step = (1.0 - 2.0*m_random.nextBool())*m_properties->stepLength();
        particle[moveDimension] += step;
        if(!currentModel->isInVoid(particle.position())) {
            // Reject. We collided with a wall
            particle[moveDimension] -= step;
        }
    }
    currentModel->stop();
    m_time += m_properties->dt();

    for(QVariant &obj : m_statistics) {
        Statistic *statistic = obj.value<Statistic*>();
        statistic->tick(this);
    }

    return true;
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

float System::time() const
{
    return m_time;
}
 QVariantList System::statistics() const
{
    return m_statistics;
}


void System::setProperties(SystemProperties *properties)
{
    if (m_properties == properties)
        return;

    m_properties = properties;
    emit propertiesChanged(properties);
}

void System::setTime(float time)
{
    if (m_time == time)
        return;

    m_time = time;
    emit timeChanged(time);
}

void System::setStatistics(QVariantList statistics)
{
    if (m_statistics == statistics)
        return;

    m_statistics = statistics;
    emit statisticsChanged(statistics);
}

float SystemProperties::stepLength() const
{
    return m_stepLength;
}

bool SystemProperties::willReset() const
{
    return m_willReset;
}

int SystemProperties::numberOfParticles() const
{
    return m_numberOfParticles;
}

int SystemProperties::posMin() const
{
    return m_posMin;
}

int SystemProperties::posMax() const
{
    return m_posMax;
}

float SystemProperties::dt() const
{
    return m_dt;
}

Model *SystemProperties::model() const
{
    return m_model;
}

void System::createParticles(int numberOfParticles, float from, float to)
{
    if(!m_properties) return;
    m_particles.resize(numberOfParticles);
    for(Particle &particle : m_particles) {
        bool isInVoid = false;
        while(!isInVoid) {
            particle.setPosition(m_random.nextQVector3D(from,to));
            particle.setOriginalPosition(particle.position());
            isInVoid = m_properties->m_model->isInVoid(particle.position());
        }
    }
}

void SystemProperties::setStepLength(float stepLength)
{
    if (m_stepLength == stepLength)
        return;

    m_stepLength = stepLength;
    emit stepLengthChanged(stepLength);
}

void SystemProperties::setWillReset(bool willReset)
{
    if (m_willReset == willReset)
        return;

    m_willReset = willReset;
    emit willResetChanged(willReset);
}

void SystemProperties::setNumberOfParticles(int numberOfParticles)
{
    if (m_numberOfParticles == numberOfParticles)
        return;

    m_numberOfParticles = numberOfParticles;
    emit numberOfParticlesChanged(numberOfParticles);
}

void SystemProperties::setPosMin(int posMin)
{
    if (m_posMin == posMin)
        return;

    m_posMin = posMin;
    emit posMinChanged(posMin);
}

void SystemProperties::setPosMax(int posMax)
{
    if (m_posMax == posMax)
        return;

    m_posMax = posMax;
    emit posMaxChanged(posMax);
}

void SystemProperties::setDt(float dt)
{
    if (m_dt == dt)
        return;

    m_dt = dt;
    emit dtChanged(dt);
}

void SystemProperties::setModel(Model *model)
{
    if (m_model == model)
        return;

    m_model = model;
    emit modelChanged(model);
}
