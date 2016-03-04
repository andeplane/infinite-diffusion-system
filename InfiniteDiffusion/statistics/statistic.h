#pragma once

#include <QObject>
#include "datasource.h"
class Statistic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataSource* dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)

protected:
    DataSource* m_dataSource = nullptr;
    bool m_readyToCompute = false;

public:
    explicit Statistic(QObject *parent = 0);
    DataSource* dataSource() const;
    virtual void compute() = 0;
    virtual void tick(class System *system) = 0;
    virtual void reset() = 0;

signals:

    void dataSourceChanged(DataSource* dataSource);

public slots:
    void setDataSource(DataSource* dataSource);
};
