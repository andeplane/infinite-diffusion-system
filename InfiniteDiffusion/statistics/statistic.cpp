#include "statistic.h"

Statistic::Statistic(QObject *parent) : QObject(parent)
{
    m_dataSource = new DataSource();
}

DataSource *Statistic::dataSource() const
{
    return m_dataSource;
}

void Statistic::setDataSource(DataSource *dataSource)
{
    if (m_dataSource == dataSource)
        return;

    m_dataSource = dataSource;
    emit dataSourceChanged(dataSource);
}
