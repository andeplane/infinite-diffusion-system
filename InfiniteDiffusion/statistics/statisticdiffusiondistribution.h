//#pragma once
//#include "statistic.h"
//#include <QVector>
//#include <QVector3D>

//class DiffusionDistributionData
//{
//public:
//    DiffusionDistributionData(const QVector<QVector3D> &positions, float timestamp)
//    {
//        m_positions = positions;
//        m_timestamp = timestamp;
//    }
//    ~DiffusionDistributionData()
//    {
//        m_positions.clear();
//    }

//    QVector<QVector3D> m_positions;
//    float m_timestamp = 0;
//};

//class StatisticDiffusionDistribution : public Statistic
//{
//    Q_OBJECT
//    Q_PROPERTY(int histogramBins READ histogramBins WRITE setHistogramBins NOTIFY histogramBinsChanged)
//    Q_PROPERTY(float mean READ mean WRITE setMean NOTIFY meanChanged)
//    Q_PROPERTY(float standardDeviation READ standardDeviation WRITE setStandardDeviation NOTIFY standardDeviationChanged)
//    Q_PROPERTY(float timeBetweenSampling READ timeBetweenSampling WRITE setTimeBetweenSampling NOTIFY timeBetweenSamplingChanged)
//    Q_PROPERTY(float fractionOfMaxDeltaTSampling READ fractionOfMaxDeltaTSampling WRITE setFractionOfMaxDeltaTSampling NOTIFY fractionOfMaxDeltaTSamplingChanged)
//    Q_PROPERTY(float timeBetweenComputing READ timeBetweenComputing WRITE setTimeBetweenComputing NOTIFY timeBetweenComputingChanged)

//private:
//    QVector<DiffusionDistributionData*> m_timesteps;
//    QVector<float> m_diffusionCoefficients;
//    int m_histogramBins = 200;
//    float m_mean = 0;
//    float m_standardDeviation = 0;
//    float m_lastSamplingTimestamp = 0;
//    float m_lastComputeTimestamp = 0;
//    float m_timeBetweenSampling = 1000;
//    float m_fractionOfMaxDeltaTSampling = 0.5;
//    float m_timeBetweenComputing = 1000;

//public:
//    StatisticDiffusionDistribution();
//    ~StatisticDiffusionDistribution();
//    void addData(const QVector<QVector3D> &positions, float timestep);
//    void computeHistogram(float smallestDiffusionCoefficient, float largestDiffusionCoefficient, DataSource &dataSource, QVector<float> &diffusionCoefficients);
//    void computeTwoTimesteps(const QVector<QVector3D> &positions_i, const QVector<QVector3D> &positions_j, const float deltaT, QVector<float> &diffusionCoefficients);
//    int histogramBins() const;
//    float mean() const;
//    float standardDeviation() const;
//    float timeBetweenSampling() const;
//    void compute();
//    virtual void tick(System *system);
//    virtual void reset();
//    float fractionOfMaxDeltaTSampling() const;
//    float timeBetweenComputing() const;

//public slots:
//    void setHistogramBins(int histogramBins);
//    void setMean(float mean);
//    void setStandardDeviation(float standardDeviation);
//    void setTimeBetweenSampling(float timeBetweenSampling);
//    void setFractionOfMaxDeltaTSampling(float fractionOfMaxDeltaTSampling);
//    void setTimeBetweenComputing(float timeBetweenComputing);

//signals:
//    void histogramBinsChanged(int histogramBins);
//    void meanChanged(float mean);
//    void standardDeviationChanged(float standardDeviation);
//    void timeBetweenSamplingChanged(float timeBetweenSampling);
//    void fractionOfMaxDeltaTSamplingChanged(float fractionOfMaxDeltaTSampling);
//    void timeBetweenComputingChanged(float timeBetweenComputing);
//};
