#include "system.h"
#include <QDebug>

void System::applyPeriodic(QVector3D &pos)
{
    const float posMin = m_properties->posMin();
    const float posMax = m_properties->posMax();
    const float delta = m_properties->posMax() - m_properties->posMin();

    if(pos[0] < posMin) pos[0] += delta;
    else if(pos[0] > posMax) pos[0] -= delta;

    if(pos[1] < posMin) pos[1] += delta;
    else if(pos[1] > posMax) pos[1] -= delta;

    if(pos[2] < posMin) pos[2] += delta;
    else if(pos[2] > posMax) pos[2] -= delta;
}

System::System()
{

}

System::~System()
{
    for(QVariant &obj : m_statistics) {
        Statistic *statistic = obj.value<Statistic*>();
        delete statistic;
    }
    m_statistics.clear();
    delete m_properties;
}

bool System::tick()
{
    if(!m_properties->model()) return false;

    if(m_properties->willReset()) {
        m_properties->model()->start();
        m_properties->setWillReset(false);
        m_time = 0;
        qDebug() << "Creating particles...";
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
        QVector3D newPosition = particle.position();

        int moveDimension = Random::nextInt(0,2);
        // double step = (1.0 - 2.0*m_random.nextBool())*m_properties->stepLength();
        double step = Random::nextGaussian(0, m_properties->stepLength());
        newPosition[moveDimension] += step;

        if(m_properties->periodic()) applyPeriodic(newPosition);

        if(currentModel->isInVoid(newPosition)) {
            // Accept, still in void
            particle.addPositionComponent(moveDimension, step);
            if(m_properties->periodic()) applyPeriodic(particle.position());
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

QVector<QVector3D> System::particlePositionsUnwrapped()
{
    QVector<QVector3D> positions;
    positions.reserve(m_particles.size());
    for(Particle &particle : m_particles) {
        positions.push_back(particle.positionUnwrapped());
        // positions.push_back(particle.position());
    }
    return positions;
}

float System::time() const
{
    return m_time;
}

QVariantList &System::statistics()
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

SystemProperties::~SystemProperties()
{
//    if(m_model) delete m_model;
//    m_model = nullptr;
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
    Model *currentModel = m_properties->m_model;
#ifdef STARTMIDDLE
    float delta = to - from;
    float boxMiddle = from + delta*0.5;

    QVector3D startPos(boxMiddle, boxMiddle, boxMiddle);

    while(!currentModel->isInVoid(startPos)) {
        startPos[0] += Random::nextFloat(-1, 1);
        startPos[1] += Random::nextFloat(-1, 1);
        startPos[2] += Random::nextFloat(-1, 1);
    }
#endif
    for(Particle &particle : m_particles) {
#ifdef STARTMIDDLE
        particle.setPosition(startPos);
        particle.setPositionUnwrapped(startPos);
#else
        bool isInVoid = false;
        while(!isInVoid) {
            particle.setPosition(Random::nextQVector3D(from,to));
            particle.setPositionUnwrapped(particle.position());
            isInVoid = currentModel->isInVoid(particle.position());
        }
#endif
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

void SystemProperties::setPeriodic(bool periodic)
{
    if (m_periodic == periodic)
        return;

    m_periodic = periodic;
    emit periodicChanged(periodic);
}

bool SystemProperties::periodic() const
{
    return m_periodic;
}
