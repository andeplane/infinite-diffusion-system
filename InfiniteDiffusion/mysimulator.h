#pragma once
#include <SimVis/Simulator>
#include "system.h"

#include <QVector>
#include <QVector3D>

class MyWorker : public SimulatorWorker
{
    Q_OBJECT
private:
    System m_system;

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
private:

public:
    MySimulator();

    // Simulator interface
protected:
    virtual SimulatorWorker *createWorker();
};
