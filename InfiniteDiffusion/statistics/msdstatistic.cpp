#include "msdstatistic.h"
#include "../system.h"

MSDStatistic::MSDStatistic()
{

}

MSDStatistic::~MSDStatistic()
{
    compute();
    m_dataSource->save(m_filename);
    reset();
}

void MSDStatistic::computeTwoTimesteps(const QVector<QVector3D> &positions_i, const QVector<QVector3D> &positions_j, const float deltaT, QVector<float> &msd) {
    if(positions_i.size() != positions_j.size()) {
        qFatal("Error in StatisticDiffusionDistribution::computeTwoTimesteps(). Two timesteps differ in number of particles.");
    }

    for(int particleIndex = 0; particleIndex < positions_j.size(); particleIndex++) {
        const QVector3D &position_i = positions_i[particleIndex];
        const QVector3D &position_j = positions_j[particleIndex];
        const float rSquared = (position_i - position_j).lengthSquared();
        msd.push_back(rSquared);
    }
}

void MSDStatistic::compute()
{
    if(m_data.size() == 0) return;
    if(m_data.size() < 2) return;

    QVector<QPointF> points;
    for(int i=1; i<m_data.size(); i++) {
        float deltaT = m_data[i]->time - m_data[0]->time;
        const QVector<QVector3D> &positions_i = m_data[0]->positions;
        const QVector<QVector3D> &positions_j = m_data[i]->positions;
        if(positions_i.size() != positions_j.size()) {
            qDebug() << "Error in MSDStatistic::compute(). Two timesteps have different number of particles";
            exit(1);
        }

        double rsqSum = 0;

        for(int particleIndex = 0; particleIndex<m_data[i]->positions.size(); particleIndex++) {
            double rsq = (positions_i[particleIndex] - positions_j[particleIndex]).lengthSquared();
            rsqSum += rsq;
        }
        rsqSum /= positions_i.size();
        points.append(QPointF(deltaT, rsqSum));
    }

    m_dataSource->clear();
    m_dataSource->setPoints(points);
    m_dataSource->update();

//    int numberOfParticles = m_data.front()->positions.size();
//    QVector<float> msdValues;
//    msdValues.reserve(0.5*m_data.size()*(m_data.size()-1)*numberOfParticles);

//    for(int i=0; i<m_data.size(); i++) {
//        const float timestamp_i = m_data[i]->time;
//        const QVector<QVector3D> &positions_i = m_data[i]->positions;
//        for(int j=i+1; j<m_data.size(); j++) {
//            const float timestamp_j = m_data[j]->time;
//            const float deltaT = timestamp_j - timestamp_i;
//            const QVector<QVector3D> &positions_j = m_data[j]->positions;
//            computeTwoTimesteps(positions_i, positions_j, deltaT, msdValues);
//        }
//    }

//    computeHistogram(*m_dataSource, msdValues);
}

void MSDStatistic::tick(System *system)
{
    if(system->particlePositionsUnwrapped().size() == 0) return;

    float deltaT = system->time() - m_lastMeasureTime;
    if(deltaT > m_measureEvery || m_lastMeasureTime == 0) {
        MSDData *data = new MSDData();
        data->positions = system->particlePositionsUnwrapped();
        data->time = system->time();
        m_lastMeasureTime = system->time();
        m_data.push_back(data);
    }

    deltaT = system->time() - m_lastComputeTime;
    if(deltaT > m_computeEvery || m_lastComputeTime == 0) {
        compute();
        m_lastComputeTime = system->time();
    }
}

void MSDStatistic::reset()
{
    for(MSDData *data : m_data) {
        delete data;
    }
    m_data.clear();
    m_lastComputeTime = m_lastMeasureTime = 0.0;
}

float MSDStatistic::measureEvery() const
{
    return m_measureEvery;
}

float MSDStatistic::computeEvery() const
{
    return m_computeEvery;
}

void MSDStatistic::setMeasureEvery(float measureEvery)
{
    if (m_measureEvery == measureEvery)
        return;

    m_measureEvery = measureEvery;
    emit measureEveryChanged(measureEvery);
}

void MSDStatistic::setComputeEvery(float computeEvery)
{
    if (m_computeEvery == computeEvery)
        return;

    m_computeEvery = computeEvery;
    emit computeEveryChanged(computeEvery);
}
