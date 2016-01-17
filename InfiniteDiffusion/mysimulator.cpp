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

void MyWorker::createHistogram(int bins)
{
    m_histogram.clear();;
    float minValue = 1e10;
    float maxValue = 0;
    QVector<float> diffusionCoefficients;
#ifdef __INTEL_COMPILER
    int numberOfParticles = m_system->positions().size();
    diffusionCoefficients.reserve(numberOfParticles);
    for(int i=0; i<numberOfParticles; i++) {
        float deltaR2 = (m_system->positions()[i] - m_system->originalPositions()[i]).lengthSquared();
        float deltaR2OverT = deltaR2 / (6*m_time);
        minValue = std::min(minValue, deltaR2OverT);
        maxValue = std::max(maxValue, deltaR2OverT);
        diffusionCoefficients.push_back(deltaR2OverT);
    }
#else
    diffusionCoefficients.reserve(m_system->particles().size());
    for(Particle &particle : m_system->particles()) {
        float deltaR2 = (particle.position() - particle.originalPosition()).lengthSquared();
        float deltaR2OverT = deltaR2 / (6*m_time);
        minValue = std::min(minValue, deltaR2OverT);
        maxValue = std::max(maxValue, deltaR2OverT);
        diffusionCoefficients.push_back(deltaR2OverT);
    }
#endif
    gsl_histogram *hist = gsl_histogram_alloc (bins);
    qDebug() << "Min: " << minValue;
    qDebug() << "Max: " << maxValue;
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
    m_system->tick();
    m_totalWorkTime += m_elapsedTimer.elapsed();
    createHistogram(100);

}
