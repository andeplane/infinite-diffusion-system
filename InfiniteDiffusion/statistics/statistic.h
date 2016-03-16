#pragma once

#include <QObject>
#include "datasource.h"
class Statistic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataSource* dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    Q_PROPERTY(QString fileExtension READ fileExtension WRITE setFileExtension NOTIFY fileExtensionChanged)
    Q_PROPERTY(int histogramBins READ histogramBins WRITE setHistogramBins NOTIFY histogramBinsChanged)

protected:
    int m_histogramBins = 100;
    QString m_filename;
    QString m_fileExtension = "txt";
    DataSource* m_dataSource = nullptr;
    bool m_readyToCompute = false;
    int m_fileCounter = 0;
    void findMinAndMax(const QVector<float> &array, float &min, float &max);
public:
    explicit Statistic(QObject *parent = 0);
    DataSource* dataSource() const;
    virtual void tick(class System *system) = 0;
    virtual void reset() = 0;
    QString filename() const;

    QString fileExtension() const;

    void computeHistogram(DataSource &dataSource, QVector<float> &values);
    int histogramBins() const;

signals:
    void dataSourceChanged(DataSource* dataSource);
    void filenameChanged(QString filename);

    void fileExtensionChanged(QString fileExtension);

    void histogramBinsChanged(int histogramBins);

public slots:
    void setDataSource(DataSource* dataSource);
    void setFilename(QString filename);
    void setFileExtension(QString fileExtension);
    void setHistogramBins(int histogramBins);
};
