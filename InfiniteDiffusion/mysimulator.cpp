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

int MySimulator::time() const
{
    return m_time;
}

float MySimulator::timePerTimestep() const
{
    return m_timePerTimestep;
}

void MySimulator::setSystem(System *system)
{
    if (m_system == system)
        return;

    m_system = system;
    emit systemChanged(system);
}

void MySimulator::setTime(int time)
{
    if (m_time == time)
        return;

    m_time = time;
    emit timeChanged(time);
}

void MySimulator::setTimePerTimestep(float timePerTimestep)
{
    if (m_timePerTimestep == timePerTimestep)
        return;

    m_timePerTimestep = timePerTimestep;
    emit timePerTimestepChanged(timePerTimestep);
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
        m_octree = mySimulator->octree();
        mySimulator->setTime(m_system->time());
        if(m_system->time()>0) {
            mySimulator->setTimePerTimestep(m_totalWorkTime / m_system->time());
        }
    }
}

void MyWorker::synchronizeRenderer(Renderable *renderableObject)
{
    Points *points = qobject_cast<Points*>(renderableObject);
    if(points) {
        QVector<QVector3D> positions = m_system->particlePositions();
        float deltaPos = (m_system->properties()->posMax() - m_system->properties()->posMin()) + m_system->properties()->posMin();
        QVector3D systemCenter(0.5*deltaPos,0.5*deltaPos,0.5*deltaPos);

        for(QVector3D &position : positions) {
            position -= systemCenter;
        }
        points->setPositions(positions);
    }
    TriangleCollection* triangleCollection = qobject_cast<TriangleCollection*>(renderableObject);
    if (m_octree!=nullptr)
    if(triangleCollection && m_octree->m_vboDirty) {
       // qDebug() << "TRIANGLE COLLECTION :" << m_octree->vboData().size() ;
        triangleCollection->data = m_octree->vboData();
        triangleCollection->dirty = true;
        m_octree->m_vboDirty = false;
     }
}

void MyWorker::work()
{
    if(!m_system) return;
    m_elapsedTimer.restart();
    bool didTick = m_system->tick();
    if(didTick) {
        m_totalWorkTime += m_elapsedTimer.elapsed();
    }
}
