#include "nogui.h"
#include "GeometryLibrary/models/models.h"
#include "statistics/statistics.h"
#include <QElapsedTimer>

NoGUI::NoGUI(CIniFile *iniFile) :
    m_iniFile(iniFile)
{
    try {
        system.setProperties(&systemProperties);
        Model *model = nullptr;
        if(iniFile->find(QString("model"), QString("void"))) {
            qDebug() << "Creating model: VoidModel";
            model = new VoidModel();
            // DO VOID
        } else if(iniFile->find(QString("model"), QString("regularnoise"))) {
            qDebug() << "Creating model: RegularNoiseModel";
            model = new RegularNoiseModel();
            model->loadParameters(iniFile);
        } else if(iniFile->find(QString("model"), QString("cylinder"))) {
            qDebug() << "Creating model: CylinderModel";
            model = new CylinderModel();
            model->loadParameters(iniFile);
        } else if(iniFile->find(QString("model"), QString("xyzfile"))) {
            qDebug() << "Creating model: XYZModel";
            model = new XYZModel();
            model->loadParameters(iniFile);
        }

        if(model) {
            systemProperties.setModel(model);
        } else {
            qDebug() << "Error, could not find model in config file.";
            exit(1);
        }

        if(iniFile->find(QString("statistic"), QString("diffusiondistribution"))) {
            qDebug() << "Adding statistic diffusiondistribution";
            StatisticDiffusionDistribution *statistic = new StatisticDiffusionDistribution();
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
        m_timesteps = iniFile->getint("numberoftimesteps");

        systemProperties.setPosMax(posmax);
        systemProperties.setPosMin(posmin);
        systemProperties.setNumberOfParticles(numberOfParticles);
        systemProperties.setStepLength(steplength);
        systemProperties.setDt(dt);
    } catch (string error) {
        cout << "Error: " << error;
    }
    system.properties()->setWillReset(true);
}

void NoGUI::run()
{
    QElapsedTimer timer;
    timer.start();
    for(int timestep=1; timestep<=m_timesteps; timestep++) {
        system.tick();
        if(timestep % 100 == 0) {
            double elapsedTime = timer.elapsed() / 1000.;
            double timePerTimestep = elapsedTime / timestep;
            int timestepsLeft = m_timesteps - timestep;
            double expectedTimeLeft = timestepsLeft*timePerTimestep;

            qDebug() << "Timestep " << timestep << " of " << m_timesteps << ". Time per timestep: " << timePerTimestep*1000 << " ms and expected time remaining: " << expectedTimeLeft << " s.";
        }
    }
}
