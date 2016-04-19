#include "nogui.h"
#include "GeometryLibrary/models/models.h"
#include "statistics/statistics.h"
#include <QElapsedTimer>

NoGUI::NoGUI(CIniFile *iniFile) :
    m_iniFile(iniFile)
{
    try {
        SystemProperties *systemProperties = new SystemProperties();
        system.setProperties(systemProperties);
        Model *model = nullptr;
        if(iniFile->find(QString("model"), QString("void"))) {
            qDebug() << "Creating model: VoidModel";
            model = new VoidModel();
            // DO VOID
        } else if(iniFile->find(QString("model"), QString("regularnoise"))) {
            qDebug() << "Creating model: RegularNoiseModel";
            model = new RegularNoiseModel();
            RegularNoiseModel *noiseModel = qobject_cast<RegularNoiseModel *>(model);
            readNoiseParameters(iniFile, noiseModel);
        } else if(iniFile->find(QString("model"), QString("cylinder"))) {
            qDebug() << "Creating model: CylinderModel";
            model = new CylinderModel();
            model->loadParameters(iniFile);
        } else if(iniFile->find(QString("model"), QString("xyzfile"))) {
            qDebug() << "Creating model: XYZModel";
            model = new XYZModel();
            model->loadParameters(iniFile);
        } else if(iniFile->find(QString("model"), QString("octree"))) {
            qDebug() << "Creating model: Octree";
            model = new Octree();
            model->loadParameters(iniFile);
        }

        if(model) {
            systemProperties->setModel(model);
        } else {
            qDebug() << "Error, could not find model in config file.";
            exit(1);
        }

        if(iniFile->find(QString("statistic"), QString("msd"))) {
            qDebug() << "Adding msd statistic";

            MSDStatistic *statistic = new MSDStatistic();
            float sampleStatisticEvery = iniFile->getdouble("statistic_sampleevery");
            statistic->setMeasureEvery(sampleStatisticEvery);
            statistic->setComputeEvery(100000000);

            QString statisticFilename = QString::fromStdString(iniFile->getstring("statistic_filename"));
            statistic->setFilename(statisticFilename);
            system.statistics().append(QVariant::fromValue(statistic));
        }

        float posmin = iniFile->getdouble("posmin");
        qDebug() << "Settings posmin: " << posmin;
        float posmax = iniFile->getdouble("posmax");
        qDebug() << "Settings posmax: " << posmax;
        float steplength = iniFile->getdouble("steplength");
        qDebug() << "Settings steplength: " << steplength;
        float dt = iniFile->getdouble("dt");
        qDebug() << "Settings dt: " << dt;
        int numberOfParticles = iniFile->getint("numberofparticles");
        qDebug() << "Settings numberofparticles: " << numberOfParticles;
        bool periodic = iniFile->getbool("periodic");
        qDebug() << "Settings periodic: " << periodic;
        bool mirrored = iniFile->getbool("mirrored");
        qDebug() << "Settings mirrored: " << mirrored;
        m_timesteps = iniFile->getint("numberoftimesteps");

        systemProperties->setPosMax(posmax);
        systemProperties->setPosMin(posmin);
        systemProperties->setNumberOfParticles(numberOfParticles);
        systemProperties->setStepLength(steplength);
        systemProperties->setPeriodic(periodic);
        systemProperties->setMirrored(mirrored);
        systemProperties->setDt(dt);
    } catch (string error) {
        cout << "Error: " << error;
    }
    system.properties()->setWillReset(true);
}

bool NoGUI::tick() {
    m_currentTimestep++;
    bool didTick = system.tick();
    if(!timer.isValid()) timer.start();

    if(m_currentTimestep % 100 == 0) {
        double elapsedTime = timer.elapsed() / 1000.;
        double timePerTimestep = elapsedTime / m_currentTimestep;
        int timestepsLeft = m_timesteps - m_currentTimestep;
        double expectedTimeLeft = timestepsLeft*timePerTimestep;

        qDebug() << "Timestep " << m_currentTimestep << " of " << m_timesteps << ". Time per timestep: " << timePerTimestep*1000 << " ms and expected time remaining: " << expectedTimeLeft << " s.";
    }
    if(m_currentTimestep == m_timesteps) {
        finished = true;
    }
    return didTick;
}

void NoGUI::run()
{
    for(int timestep=1; timestep<=m_timesteps; timestep++) {
        tick();
    }

    qDebug() << "Simulation finished after " << timer.elapsed() / 1000.  << " seconds.";
}
