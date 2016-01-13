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
    Q_PROPERTY(Geometry* diffusionGeometry READ diffusionGeometry WRITE setDiffusionGeometry NOTIFY diffusionGeometryChanged)
private:
    Geometry* m_diffusionGeometry = nullptr;

public:
    MySimulator();
    Geometry* diffusionGeometry() const;

public slots:
    void setDiffusionGeometry(Geometry* diffusionGeometry);

signals:
    void diffusionGeometryChanged(Geometry* diffusionGeometry);

protected:
    virtual SimulatorWorker *createWorker();
};
