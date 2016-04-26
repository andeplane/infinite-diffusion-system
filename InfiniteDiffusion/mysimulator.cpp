#include "mysimulator.h"
#include "nogui.h"
#include <QDebug>
#include <SimVis/Points>
#include <SimVis/Spheres>

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

Octree *MySimulator::octree() const
{
    return m_octree;
}

NoGUI *MySimulator::noGUI() const
{
    return m_noGUI;
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

void MySimulator::setOctree(Octree *octree)
{
    if (m_octree == octree)
        return;

    m_octree = octree;
    emit octreeChanged(octree);
}

void MySimulator::setNoGUI(NoGUI *noGUI)
{
    if (m_noGUI == noGUI)
        return;

    m_noGUI = noGUI;
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
        m_noGUI = mySimulator->noGUI();
        mySimulator->setTime(m_system->time());
        if(m_system->time()>0) {
            mySimulator->setTimePerTimestep(m_totalWorkTime / m_system->time());
        }
    }
}

void MyWorker::synchronizeRenderer(Renderable *renderableObject)
{
    Points *points = qobject_cast<Points*>(renderableObject);
    float deltaPos = (m_system->properties()->posMax() - m_system->properties()->posMin()) + m_system->properties()->posMin();
    QVector3D systemCenter(0.5*deltaPos,0.5*deltaPos,0.5*deltaPos);

    if(points) {
        // QVector<QVector3D> positions = m_system->particlePositionsUnwrapped();
        QVector<QVector3D> positions = m_system->particlePositions();

        for(QVector3D &position : positions) {
            position -= systemCenter;
        }
        points->setPositions(positions);
    }
    TriangleCollection* triangleCollection = qobject_cast<TriangleCollection*>(renderableObject);
    if(m_octree!=nullptr && triangleCollection && m_octree->m_vboDirty) {
       // qDebug() << "TRIANGLE COLLECTION :" << m_octree->vboData().size() ;
        triangleCollection->data = m_octree->vboData();
        for(SimVis::TriangleCollectionVBOData &p : triangleCollection->data) {
            p.vertex -= systemCenter;
        }
        triangleCollection->dirty = true;
        m_octree->m_vboDirty = false;
     }

    Spheres *spheres = qobject_cast<Spheres*>(renderableObject);
    if(spheres) {

        QVector<QVector3D> positions = m_system->particlePositions();
        for(QVector3D &position : positions) {
            position -= systemCenter;
        }
        spheres->positions() = positions;
        spheres->setDirty(true);
        return;
    }


}

void MyWorker::work()
{
    if(!m_system) return;
    m_elapsedTimer.restart();
    bool didTick;
    if(m_noGUI) {
        didTick = m_noGUI->tick();
        if(m_noGUI->finished) {
            exit(0);
        }
    } else {
        didTick = m_system->tick();
    }
    if(didTick) {
        m_totalWorkTime += m_elapsedTimer.elapsed();
    }
}
