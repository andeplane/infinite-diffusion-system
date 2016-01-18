#pragma once

#include <QObject>
#include "QMLPlot/linegraph.h"

class Statistic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LineGraphDataSource* dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)

protected:
    LineGraphDataSource* m_dataSource = nullptr;
    bool m_readyToCompute = false;

public:
    explicit Statistic(QObject *parent = 0);
    LineGraphDataSource* dataSource() const;
    void normalizeHistogram(QVector<QPointF> &histogram);
    virtual void compute() = 0;
    virtual void tick(class System *system) = 0;
    virtual void reset() = 0;

signals:
    void dataSourceChanged(LineGraphDataSource* dataSource);

public slots:
    void setDataSource(LineGraphDataSource* dataSource);
};
