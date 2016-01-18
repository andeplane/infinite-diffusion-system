#include "mysimulator.h"
#include <QDebug>
#include <SimVis/Points>

MySimulator::MySimulator()
{

}

System *MySimulator::system() const
{
    return m_system;
}

LineGraphDataSource *MySimulator::lineGraphDataSource() const
{
    return m_lineGraphDataSource;
}

float MySimulator::diffusionMean() const
{
    return m_diffusionMean;
}

float MySimulator::diffusionStandardDeviation() const
{
    return m_diffusionStandardDeviation;
}

int MySimulator::time() const
{
    return m_time;
}

float MySimulator::timePerTimestep() const
{
    return m_timePerTimestep;
}

int MySimulator::histogramBins() const
{
    return m_histogramBins;
}

void MySimulator::setSystem(System *system)
{
    if (m_system == system)
        return;

    m_system = system;
    emit systemChanged(system);
}

void MySimulator::setLineGraphDataSource(LineGraphDataSource *lineGraphDataSource)
{
    if (m_lineGraphDataSource == lineGraphDataSource)
        return;

    m_lineGraphDataSource = lineGraphDataSource;
    emit lineGraphDataSourceChanged(lineGraphDataSource);
}

void MySimulator::setDiffusionMean(float diffusionMean)
{
    if (m_diffusionMean == diffusionMean)
        return;

    m_diffusionMean = diffusionMean;
    emit diffusionMeanChanged(diffusionMean);
}

void MySimulator::setDiffusionStandardDeviation(float diffusionStandardDeviation)
{
    if (m_diffusionStandardDeviation == diffusionStandardDeviation)
        return;

    m_diffusionStandardDeviation = diffusionStandardDeviation;
    emit diffusionStandardDeviationChanged(diffusionStandardDeviation);
}

void MySimulator::setTime(int time)
{
    if (m_time == time)
        return;

    m_time = time;
    emit timeChanged(time);
}

void MySimulator::setTimePerTimestep(float timePerTimestep)
{
    if (m_timePerTimestep == timePerTimestep)
        return;

    m_timePerTimestep = timePerTimestep;
    emit timePerTimestepChanged(timePerTimestep);
}

void MySimulator::setHistogramBins(int histogramBins)
{
    if (m_histogramBins == histogramBins)
        return;

    m_histogramBins = histogramBins;
    emit histogramBinsChanged(histogramBins);
}

SimulatorWorker *MySimulator::createWorker()
{
    return new MyWorker();
}

MyWorker::MyWorker()
{

}

void MyWorker::synchronizeSimulator(Simulator *simulator)
{
    MySimulator *mySimulator = qobject_cast<MySimulator*>(simulator);
    if(mySimulator) {
        // Synchronize data between QML thread and computing thread (MySimulator is on QML, MyWorker is computing thread).
        // This is for instance data from user through GUI (sliders, buttons, text fields etc)
        m_system = mySimulator->system();
        if(mySimulator->lineGraphDataSource()) {
            mySimulator->lineGraphDataSource()->setPoints(m_histogram);
        }
        mySimulator->setDiffusionMean(m_diffusionMean);
        mySimulator->setDiffusionStandardDeviation(m_diffusionStandardDeviation);
        mySimulator->setTime(m_time);
        m_histogramBins = mySimulator->histogramBins();
        if(m_time>0) {
            mySimulator->setTimePerTimestep(m_totalWorkTime / m_time);
        }
    }
}

void MyWorker::synchronizeRenderer(Renderable *renderableObject)
{
    Points *points = qobject_cast<Points*>(renderableObject);
    if(points) {
        QVector<QVector3D> positions = m_system->particlePositions();
        points->setPositions(positions);
    }
}

void MyWorker::normalizeHistogram() {
    double integralSum = 0;
    for(int i=0; i<m_histogram.size()-1; i++) {
        QPointF &p1 = m_histogram[i];
        QPointF &p2 = m_histogram[i+1];
        double dx = p2.x() - p1.x();
        double dy = p2.y() + p1.y();
        integralSum += dx*dy;
    }
    integralSum *= 0.5;
    for(QPointF &point : m_histogram) {
        point.setY(point.y()/integralSum);
    }
}

void MyWorker::createHistogram(int bins)
{
    m_histogram.clear();
    if(m_system->particles().size() == 0) return;

    float minValue = 1e10;
    float maxValue = 0;
    QVector<float> diffusionCoefficients;
    diffusionCoefficients.reserve(m_system->particles().size());

    for(Particle &particle : m_system->particles()) {
        float deltaR2 = (particle.position() - particle.originalPosition()).lengthSquared();
        float deltaR2OverT = deltaR2 / (6*m_time);
        minValue = std::min(minValue, deltaR2OverT);
        maxValue = std::max(maxValue, deltaR2OverT);
        diffusionCoefficients.push_back(deltaR2OverT);
    }
    if(minValue >= maxValue) return;

    gsl_histogram *hist = gsl_histogram_alloc (bins);
    gsl_histogram_set_ranges_uniform (hist, minValue, maxValue);
    for(const float &value : diffusionCoefficients) {
        gsl_histogram_increment (hist, value);
    }

    m_histogram.resize(bins);
    for(int i=0; i<bins; i++) {
        double upper, lower;
        gsl_histogram_get_range(hist, i, &lower, &upper);
        float middle = 0.5*(upper+lower);
        m_histogram[i].setX(middle);
        m_histogram[i].setY(gsl_histogram_get(hist,i));
    }
    normalizeHistogram();

    m_diffusionMean = gsl_histogram_mean(hist);
    m_diffusionStandardDeviation = gsl_histogram_sigma(hist);

    gsl_histogram_free (hist);
    diffusionCoefficients.clear();
}

void MyWorker::work()
{
    if(!m_system) return;
    m_time++;
    m_elapsedTimer.restart();
    bool didTick = m_system->tick();
    m_totalWorkTime += m_elapsedTimer.elapsed();
    if(didTick) createHistogram(m_histogramBins);

}
