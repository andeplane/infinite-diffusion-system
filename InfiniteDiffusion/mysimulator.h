#pragma once
#include <SimVis/Simulator>
#include "system.h"
#include <gsl/gsl_histogram.h>
#include <QVector>
#include <QVector3D>
#include <QElapsedTimer>
class MyWorker : public SimulatorWorker
{
    Q_OBJECT
private:
    QElapsedTimer m_elapsedTimer;
    System *m_system = nullptr;
    QVector<QPointF> m_histogram;
    Octree* m_octree = nullptr;
    class NoGUI* m_noGUI = nullptr;
    float m_diffusionMean = 0;
    float m_diffusionStandardDeviation = 0;
    double m_totalWorkTime = 0;
    int m_histogramBins = 100;
    // SimulatorWorker interface
    virtual void synchronizeSimulator(Simulator *simulator);
    virtual void synchronizeRenderer(Renderable *renderableObject);
    virtual void work();
    void createHistogram(int bins);
    void normalizeHistogram();
public:
    MyWorker();
};

class MySimulator : public Simulator
{
    Q_OBJECT
    Q_PROPERTY(System* system READ system WRITE setSystem NOTIFY systemChanged)
    Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(float timePerTimestep READ timePerTimestep WRITE setTimePerTimestep NOTIFY timePerTimestepChanged)
    Q_PROPERTY(Octree* octree READ octree WRITE setOctree NOTIFY octreeChanged)
private:
    System* m_system = nullptr;
    int m_time = 0;
    float m_timePerTimestep = 0;
    Octree* m_octree = nullptr;
    class NoGUI* m_noGUI = nullptr;

public:
    MySimulator();
    System* system() const;
    int time() const;
    float timePerTimestep() const;
    Octree* octree() const;
    class NoGUI* noGUI() const;

public slots:
    void setSystem(System* system);
    void setTime(int time);
    void setTimePerTimestep(float timePerTimestep);
    void setOctree(Octree* octree);
    void setNoGUI(class NoGUI* noGUI);

signals:
    void systemChanged(System* system);
    void timeChanged(int time);
    void timePerTimestepChanged(float timePerTimestep);
    void octreeChanged(Octree* octree);

protected:
    virtual SimulatorWorker *createWorker();
};
