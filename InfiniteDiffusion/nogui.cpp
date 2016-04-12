#include "nogui.h"
#include "GeometryLibrary/models/models.h"
#include "statistics/statistics.h"
#include <QElapsedTimer>

void NoGUI::readNoiseParameters(CIniFile *iniFile, RegularNoiseModel *noiseModel) {
    if(QString::fromStdString((iniFile->getstring("noise_properties_filename"))).isEmpty()) {
        noiseModel->parameters()->setValue("octaves", iniFile->getdouble("noise_octaves"));
        noiseModel->parameters()->setValue("scale", iniFile->getdouble("noise_scale"));
        noiseModel->parameters()->setValue("persistence", iniFile->getdouble("noise_persistence"));
        noiseModel->parameters()->setValue("threshold", iniFile->getdouble("noise_threshold"));
        noiseModel->parameters()->setValue("inverted", iniFile->getbool("noise_inverted"));
        noiseModel->parameters()->setValue("seed", iniFile->getdouble("noise_seed"));
        noiseModel->parameters()->setValue("absolute", iniFile->getbool("noise_absolute"));
        noiseModel->parameters()->setValue("skewscale", iniFile->getdouble("noise_skewscale"));
        noiseModel->parameters()->setValue("skewamplitude", iniFile->getdouble("noise_skewamplitude"));
        noiseModel->parameters()->getParameter("noisetype")->setString(QString::fromStdString((iniFile->getstring("noise_noisetype"))));
    } else {
        noiseModel->parameters()->load(QString::fromStdString((iniFile->getstring("noise_properties_filename"))));
    }
}

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

        if(iniFile->find(QString("cut_noise"), true)) {
            qDebug() << "Cutting noise";
            RegularNoiseModel *noiseModel = new RegularNoiseModel();
            readNoiseParameters(iniFile, noiseModel);

            Octree *octreeModel = qobject_cast<Octree*>(model);
            XYZModel *xyzModel = qobject_cast<XYZModel*>(model);
            if(octreeModel) {
                qDebug() << "Removing from model";
                octreeModel->removeFromModel(noiseModel);
                qDebug() << "Building octree";
                octreeModel->buildTree(true);
            } else if(xyzModel) {
                qDebug() << "Removing from model";
                xyzModel->removeFromModel(noiseModel);
                qDebug() << "Updating distance to atom field";
                xyzModel->updateDistanceToAtomField();
            }
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
        m_timesteps = iniFile->getint("numberoftimesteps");

        systemProperties->setPosMax(posmax);
        systemProperties->setPosMin(posmin);
        systemProperties->setNumberOfParticles(numberOfParticles);
        systemProperties->setStepLength(steplength);
        systemProperties->setDt(dt);
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

    qDebug() << "Simulation finished after " << timer.elapsed() / 1000.  << " seconds.";
}
