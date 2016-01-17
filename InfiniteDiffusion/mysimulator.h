#pragma once
#include <SimVis/Simulator>
#include "system.h"
#include "geometry/geometries.h"
#include "gsl/gsl_histogram.h"
#include "linegraph.h"
#include <QVector>
#include <QVector3D>
#include <QElapsedTimer>

class MyWorker : public SimulatorWorker
{
    Q_OBJECT
private:
    QElapsedTimer m_elapsedTimer;
    int m_time = 0;
    System *m_system = nullptr;
    QVector<QPointF> m_histogram;
    float m_diffusionMean = 0;
    float m_diffusionStandardDeviation = 0;
    double m_totalWorkTime = 0;
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
    Q_PROPERTY(LineGraphDataSource* lineGraphDataSource READ lineGraphDataSource WRITE setLineGraphDataSource NOTIFY lineGraphDataSourceChanged)
    Q_PROPERTY(float diffusionMean READ diffusionMean WRITE setDiffusionMean NOTIFY diffusionMeanChanged)
    Q_PROPERTY(float diffusionStandardDeviation READ diffusionStandardDeviation WRITE setDiffusionStandardDeviation NOTIFY diffusionStandardDeviationChanged)
    Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(float timePerTimestep READ timePerTimestep WRITE setTimePerTimestep NOTIFY timePerTimestepChanged)
private:
    System* m_system = nullptr;
    LineGraphDataSource* m_lineGraphDataSource = nullptr;
    float m_diffusionMean = 0;
    float m_diffusionStandardDeviation = 0;
    int m_time = 0;
    float m_timePerTimestep = 0;

public:
    MySimulator();
    System* system() const;
    LineGraphDataSource* lineGraphDataSource() const;
    float diffusionMean() const;
    float diffusionStandardDeviation() const;
    int time() const;
    float timePerTimestep() const;

public slots:
    void setSystem(System* system);
    void setLineGraphDataSource(LineGraphDataSource* lineGraphDataSource);
    void setDiffusionMean(float diffusionMean);
    void setDiffusionStandardDeviation(float diffusionStandardDeviation);
    void setTime(int time);
    void setTimePerTimestep(float timePerTimestep);

signals:
    void systemChanged(System* system);
    void lineGraphDataSourceChanged(LineGraphDataSource* lineGraphDataSource);
    void diffusionMeanChanged(float diffusionMean);
    void diffusionStandardDeviationChanged(float diffusionStandardDeviation);
    void timeChanged(int time);
    void timePerTimestepChanged(float timePerTimestep);

protected:
    virtual SimulatorWorker *createWorker();
};