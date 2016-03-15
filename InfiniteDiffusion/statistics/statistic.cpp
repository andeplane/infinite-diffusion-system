#include "statistic.h"

Statistic::Statistic(QObject *parent) : QObject(parent)
{
    m_dataSource = new DataSource();
}

DataSource *Statistic::dataSource() const
{
    return m_dataSource;
}

void Statistic::save()
{
    QString fullFilename = QString("%1_%2.%3").arg(m_filename).arg(m_fileCounter++, 4, 10, QChar('0')).arg(m_fileExtension);
    if(m_dataSource) m_dataSource->save(fullFilename);
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

void Statistic::setFileExtension(QString fileExtension)
{
    if (m_fileExtension == fileExtension)
        return;

    m_fileExtension = fileExtension;
    emit fileExtensionChanged(fileExtension);
}
