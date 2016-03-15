#pragma once

#include <QObject>
#include "datasource.h"
class Statistic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataSource* dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    Q_PROPERTY(QString fileExtension READ fileExtension WRITE setFileExtension NOTIFY fileExtensionChanged)

protected:
    QString m_filename;
    QString m_fileExtension = "txt";
    DataSource* m_dataSource = nullptr;
    bool m_readyToCompute = false;
    int m_fileCounter = 0;

public:
    explicit Statistic(QObject *parent = 0);
    DataSource* dataSource() const;
    virtual void save();
    virtual void compute() = 0;
    virtual void tick(class System *system) = 0;
    virtual void reset() = 0;
    QString filename() const;

    QString fileExtension() const;

signals:
    void dataSourceChanged(DataSource* dataSource);
    void filenameChanged(QString filename);

    void fileExtensionChanged(QString fileExtension);

public slots:
    void setDataSource(DataSource* dataSource);
    void setFilename(QString filename);
    void setFileExtension(QString fileExtension);
};
