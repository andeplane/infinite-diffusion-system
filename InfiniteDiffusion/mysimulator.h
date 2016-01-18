#pragma once
#include <SimVis/Simulator>
#include "system.h"
#include "QMLPlot/linegraph.h"
#include "geometry/geometries.h"
#include "gsl/gsl_histogram.h"

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
    Q_PROPERTY(LineGraphDataSource* lineGraphDataSource READ lineGraphDataSource WRITE setLineGraphDataSource NOTIFY lineGraphDataSourceChanged)
    Q_PROPERTY(float diffusionMean READ diffusionMean WRITE setDiffusionMean NOTIFY diffusionMeanChanged)
    Q_PROPERTY(float diffusionStandardDeviation READ diffusionStandardDeviation WRITE setDiffusionStandardDeviation NOTIFY diffusionStandardDeviationChanged)
    Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(float timePerTimestep READ timePerTimestep WRITE setTimePerTimestep NOTIFY timePerTimestepChanged)
    Q_PROPERTY(int histogramBins READ histogramBins WRITE setHistogramBins NOTIFY histogramBinsChanged)
private:
    System* m_system = nullptr;
    LineGraphDataSource* m_lineGraphDataSource = nullptr;
    float m_diffusionMean = 0;
    float m_diffusionStandardDeviation = 0;
    int m_time = 0;
    float m_timePerTimestep = 0;
    int m_histogramBins = 100;

public:
    MySimulator();
    System* system() const;
    LineGraphDataSource* lineGraphDataSource() const;
    float diffusionMean() const;
    float diffusionStandardDeviation() const;
    int time() const;
    float timePerTimestep() const;
    int histogramBins() const;

public slots:
    void setSystem(System* system);
    void setLineGraphDataSource(LineGraphDataSource* lineGraphDataSource);
    void setDiffusionMean(float diffusionMean);
    void setDiffusionStandardDeviation(float diffusionStandardDeviation);
    void setTime(int time);
    void setTimePerTimestep(float timePerTimestep);
    void setHistogramBins(int histogramBins);

signals:
    void systemChanged(System* system);
    void lineGraphDataSourceChanged(LineGraphDataSource* lineGraphDataSource);
    void diffusionMeanChanged(float diffusionMean);
    void diffusionStandardDeviationChanged(float diffusionStandardDeviation);
    void timeChanged(int time);
    void timePerTimestepChanged(float timePerTimestep);
    void histogramBinsChanged(int histogramBins);

protected:
    virtual SimulatorWorker *createWorker();
};
