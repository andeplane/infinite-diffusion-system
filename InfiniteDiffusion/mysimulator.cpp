#include "mysimulator.h"
#include <QDebug>
#include <SimVis/Points>

MySimulator::MySimulator()
{

}

System *MySimulator::system() const
{
    return m_system;
}

void MySimulator::setSystem(System *system)
{
    if (m_system == system)
        return;

    m_system = system;
    emit systemChanged(system);
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
        m_system = mySimulator->system();
    }
}

void MyWorker::synchronizeRenderer(Renderable *renderableObject)
{
    Points *points = qobject_cast<Points*>(renderableObject);
    if(points) {
        QVector<QVector3D> positions = m_system->particlePositions();
        points->setPositions(positions);
    }
}

void MyWorker::work()
{
    if(!m_system) return;
}
