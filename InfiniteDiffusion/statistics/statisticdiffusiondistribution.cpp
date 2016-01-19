#include "statisticdiffusiondistribution.h"
#include "system.h"
#include <gsl/gsl_histogram.h>

StatisticDiffusionDistribution::StatisticDiffusionDistribution() : Statistic()
{

}

void StatisticDiffusionDistribution::addData(const QVector<QVector3D> &positions, float timestep)
{
    m_timesteps.push_back(new DiffusionDistributionData(positions, timestep));
}

void StatisticDiffusionDistribution::computeHistogram(float smallestDiffusionCoefficient, float largestDiffusionCoefficient)
{
    m_dataSource->clear();
    if(m_diffusionCoefficients.size() == 0) return;

    gsl_histogram *hist = gsl_histogram_alloc (m_histogramBins);
    gsl_histogram_set_ranges_uniform (hist, smallestDiffusionCoefficient, largestDiffusionCoefficient);
    for(const float &value : m_diffusionCoefficients) {
        gsl_histogram_increment (hist, value);
    }

    QVector<QPointF> &points = m_dataSource->points();
    points.resize(m_histogramBins);
    for(int i=0; i<m_histogramBins; i++) {
        double upper, lower;
        gsl_histogram_get_range(hist, i, &lower, &upper);
        float middle = 0.5*(upper+lower);
        points[i].setX(middle);
        points[i].setY(gsl_histogram_get(hist,i));
    }
    points.push_front(QPointF(0,0)); // Add a 0,0 point to make graph look nicr
    normalizeHistogram(points);
    setMean(gsl_histogram_mean(hist));
    setStandardDeviation(gsl_histogram_sigma(hist));

    m_dataSource->update();
    gsl_histogram_free(hist);
}


void StatisticDiffusionDistribution::compute()
{
    if(m_timesteps.size() == 0) return;
    float smallestDiffusionCoefficient = 1e10;
    float largestDiffusionCoefficient = 0;
    int numberOfParticles = m_timesteps.front()->m_positions.size();
    m_diffusionCoefficients.clear();
    m_diffusionCoefficients.reserve(0.5*m_timesteps.size()*(m_timesteps.size()-1)*numberOfParticles);
    float maxDeltaT = m_timesteps.last()->m_timestamp - m_timesteps.front()->m_timestamp;

    for(int i=0; i<m_timesteps.size(); i++) {
        const float timestamp_i = m_timesteps[i]->m_timestamp;
        const QVector<QVector3D> &positions_i = m_timesteps[i]->m_positions;
        for(int j=i+1; j<m_timesteps.size(); j++) {
            const float timestamp_j = m_timesteps[j]->m_timestamp;
            const float deltaT = timestamp_j - timestamp_i;
            if(deltaT < maxDeltaT*0.5) continue;
            const QVector<QVector3D> &positions_j = m_timesteps[j]->m_positions;
            if(positions_i.size() != positions_j.size()) {
                qFatal("Error in StatisticDiffusionDistribution::compute(). Two timesteps differ in number of timesteps");
            }

            for(int particleIndex = 0; particleIndex < positions_j.size(); particleIndex++) {
                const QVector3D &position_i = positions_i[particleIndex];
                const QVector3D &position_j = positions_j[particleIndex];
                const float rSquared = (position_i - position_j).lengthSquared();
                const float diffusionCoefficient = rSquared / (6*deltaT);
                smallestDiffusionCoefficient = std::min(smallestDiffusionCoefficient, diffusionCoefficient);
                largestDiffusionCoefficient = std::max(largestDiffusionCoefficient, diffusionCoefficient);
                m_diffusionCoefficients.push_back(diffusionCoefficient);
            }
        }
    }

    computeHistogram(smallestDiffusionCoefficient, largestDiffusionCoefficient);
}

float StatisticDiffusionDistribution::mean() const
{
    return m_mean;
}

float StatisticDiffusionDistribution::standardDeviation() const
{
    return m_standardDeviation;
}

void StatisticDiffusionDistribution::setHistogramBins(int histogramBins)
{
    if (m_histogramBins == histogramBins)
        return;

    m_histogramBins = histogramBins;
    emit histogramBinsChanged(histogramBins);
}

void StatisticDiffusionDistribution::setMean(float mean)
{
    if (m_mean == mean)
        return;

    m_mean = mean;
    emit meanChanged(mean);
}

void StatisticDiffusionDistribution::setStandardDeviation(float standardDeviation)
{
    if (m_standardDeviation == standardDeviation)
        return;

    m_standardDeviation = standardDeviation;
    emit standardDeviationChanged(standardDeviation);
}

void StatisticDiffusionDistribution::setTimeBetweenSampling(float timeBetweenSampling)
{
    if (m_timeBetweenSampling == timeBetweenSampling)
        return;

    m_timeBetweenSampling = timeBetweenSampling;
    emit timeBetweenSamplingChanged(timeBetweenSampling);
}

void StatisticDiffusionDistribution::setFractionOfMaxDeltaTSampling(float fractionOfMaxDeltaTSampling)
{
    if (m_fractionOfMaxDeltaTSampling == fractionOfMaxDeltaTSampling)
        return;

    m_fractionOfMaxDeltaTSampling = fractionOfMaxDeltaTSampling;
    emit fractionOfMaxDeltaTSamplingChanged(fractionOfMaxDeltaTSampling);
}

void StatisticDiffusionDistribution::setTimeBetweenComputing(float timeBetweenComputing)
{
    if (m_timeBetweenComputing == timeBetweenComputing)
        return;

    m_timeBetweenComputing = timeBetweenComputing;
    emit timeBetweenComputingChanged(timeBetweenComputing);
}

int StatisticDiffusionDistribution::histogramBins() const
{
    return m_histogramBins;
}


void StatisticDiffusionDistribution::tick(System *system)
{
    float deltaT = system->time() - m_lastSamplingTimestamp;
    if(deltaT >= m_timeBetweenSampling || system->time() == 0) {
        m_lastSamplingTimestamp = system->time();
        auto particlePositions = system->particlePositions();
        addData(particlePositions, system->time());
    }

    deltaT = system->time() - m_lastComputeTimestamp;
    if(deltaT >= m_timeBetweenComputing) {
        m_lastComputeTimestamp = system->time();
        compute();
    }
}

float StatisticDiffusionDistribution::timeBetweenSampling() const
{
    return m_timeBetweenSampling;
}


void StatisticDiffusionDistribution::reset()
{
    for(DiffusionDistributionData *data : m_timesteps) {
        delete data;
    }
    m_timesteps.clear();
    m_diffusionCoefficients.clear();
    m_dataSource->clear();
    m_lastSamplingTimestamp = 0;
}

float StatisticDiffusionDistribution::fractionOfMaxDeltaTSampling() const
{
    return m_fractionOfMaxDeltaTSampling;
}

float StatisticDiffusionDistribution::timeBetweenComputing() const
{
    return m_timeBetweenComputing;
}
