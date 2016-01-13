#include "mysimulator.h"
#include <QDebug>
MySimulator::MySimulator()
{

}

Geometry *MySimulator::diffusionGeometry() const
{
    return m_diffusionGeometry;
}

void MySimulator::setDiffusionGeometry(Geometry *diffusionGeometry)
{
    if (m_diffusionGeometry == diffusionGeometry)
        return;

    m_diffusionGeometry = diffusionGeometry;
    emit diffusionGeometryChanged(diffusionGeometry);
}

SimulatorWorker *MySimulator::createWorker()
{
    return new MyWorker();
}

MyWorker::MyWorker()
{

}

void MyWorker::synchronizeSimulator(Simulator *simulator)
{
    MySimulator *mySimulator = qobject_cast<MySimulator*>(simulator);
    if(mySimulator) {
        // Synchronize data between QML thread and computing thread (MySimulator is on QML, MyWorker is computing thread).
        // This is for instance data from user through GUI (sliders, buttons, text fields etc)
        m_system.setGeometry(mySimulator->diffusionGeometry());
    }
}

void MyWorker::synchronizeRenderer(Renderable *renderableObject)
{

}

void MyWorker::work()
{

}
