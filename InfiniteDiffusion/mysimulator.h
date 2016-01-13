#pragma once
#include <SimVis/Simulator>
#include "system.h"
#include "geometry/geometries.h"

#include <QVector>
#include <QVector3D>

class MyWorker : public SimulatorWorker
{
    Q_OBJECT
private:
    System *m_system = nullptr;

    // SimulatorWorker interface
    virtual void synchronizeSimulator(Simulator *simulator);
    virtual void synchronizeRenderer(Renderable *renderableObject);
    virtual void work();
public:
    MyWorker();
};

class MySimulator : public Simulator
{
    Q_OBJECT
    Q_PROPERTY(System* system READ system WRITE setSystem NOTIFY systemChanged)
private:
    System* m_system = nullptr;

public:
    MySimulator();
    System* system() const;

public slots:
    void setSystem(System* system);

signals:
    void systemChanged(System* system);

protected:
    virtual SimulatorWorker *createWorker();
};
