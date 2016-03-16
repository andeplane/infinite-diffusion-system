#include "statistic.h"
#include <gsl/gsl_histogram.h>

void Statistic::findMinAndMax(const QVector<float> &array, float &min, float &max)
{
    min = -1e10;
    max = 1e10;
    for(const float &value : array) {
        min = std::min(min, value);
        max = std::max(max, value);
    }
}

Statistic::Statistic(QObject *parent) : QObject(parent)
{
    m_dataSource = new DataSource();
}

DataSource *Statistic::dataSource() const
{
    return m_dataSource;
}

QString Statistic::filename() const
{
    return m_filename;
}

QString Statistic::fileExtension() const
{
    return m_fileExtension;
}

void Statistic::setDataSource(DataSource *dataSource)
{
    if (m_dataSource == dataSource)
        return;

    m_dataSource = dataSource;
    emit dataSourceChanged(dataSource);
}

void Statistic::setFilename(QString filename)
{
    if (m_filename == filename)
        return;

    m_filename = filename;
    emit filenameChanged(filename);
}

void Statistic::computeHistogram(DataSource& dataSource, QVector<float> &values)
{
    dataSource.clear();
    if(values.size() == 0) return;

    float min,max;
    findMinAndMax(values, min, max);

    gsl_histogram *hist = gsl_histogram_alloc (m_histogramBins);
    gsl_histogram_set_ranges_uniform (hist, min, max);
    for(const float &value : values) {
        gsl_histogram_increment (hist, value);
    }

    QVector<QPointF> points;
    points.resize(m_histogramBins);
    for(int i=0; i<m_histogramBins; i++) {
        double upper, lower;
        gsl_histogram_get_range(hist, i, &lower, &upper);
        float middle = 0.5*(upper+lower);
        points[i].setX(middle);
        points[i].setY(gsl_histogram_get(hist,i));
    }
    dataSource.setPoints(points, true);
    gsl_histogram_free(hist);
}

int Statistic::histogramBins() const
{
    return m_histogramBins;
}

void Statistic::setFileExtension(QString fileExtension)
{
    if (m_fileExtension == fileExtension)
        return;

    m_fileExtension = fileExtension;
    emit fileExtensionChanged(fileExtension);
}

void Statistic::setHistogramBins(int histogramBins)
{
    if (m_histogramBins == histogramBins)
        return;

    m_histogramBins = histogramBins;
    emit histogramBinsChanged(histogramBins);
}
