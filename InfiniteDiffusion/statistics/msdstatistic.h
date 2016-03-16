#ifndef MSDSTATISTIC_H
#define MSDSTATISTIC_H

#include "statistic.h"
#include <QVector>
#include <QVector3D>

struct MSDData {
    QVector<QVector3D> positions;
    float time;
};

class MSDStatistic : public Statistic
{
    Q_OBJECT
    Q_PROPERTY(float measureEvery READ measureEvery WRITE setMeasureEvery NOTIFY measureEveryChanged)
    Q_PROPERTY(float computeEvery READ computeEvery WRITE setComputeEvery NOTIFY computeEveryChanged)
public:
    MSDStatistic();
    ~MSDStatistic();
    void compute();
    virtual void tick(class System *system) override;
    virtual void reset() override;
    float measureEvery() const;
    float computeEvery() const;

public slots:
    void setMeasureEvery(float measureEvery);
    void setComputeEvery(float computeEvery);

signals:
    void measureEveryChanged(float measureEvery);
    void computeEveryChanged(float computeEvery);

private:
    float m_lastMeasureTime = 0;
    float m_lastComputeTime = 0;
    float m_measureEvery = 100;
    QVector<MSDData*> m_data;
    float m_computeEvery = 1000;
    void computeTwoTimesteps(const QVector<QVector3D> &positions_i, const QVector<QVector3D> &positions_j, const float deltaT, QVector<float> &msd);
};

#endif // MSDSTATISTIC_H
