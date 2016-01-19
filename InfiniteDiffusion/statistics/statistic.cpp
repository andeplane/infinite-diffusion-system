#include "statistic.h"

Statistic::Statistic(QObject *parent) : QObject(parent)
{
    m_dataSource = new LineGraphDataSource();
}

LineGraphDataSource *Statistic::dataSource() const
{
    return m_dataSource;
}

void Statistic::normalizeHistogram(QVector<QPointF> &histogram)
{
    // Normalize the histogram using the trapezoidal rule
    double integralSum = 0;
    for(int i=0; i<histogram.size()-1; i++) {
        QPointF &p1 = histogram[i];
        QPointF &p2 = histogram[i+1];
        double dx = p2.x() - p1.x();
        double dy = p2.y() + p1.y();
        integralSum += dx*dy;
    }
    integralSum *= 0.5;
    for(QPointF &point : histogram) {
        point.setY(point.y()/integralSum);
    }
}

void Statistic::setDataSource(LineGraphDataSource *dataSource)
{
    if (m_dataSource == dataSource)
        return;

    m_dataSource = dataSource;
    emit dataSourceChanged(dataSource);
}
