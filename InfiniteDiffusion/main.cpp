
#ifndef RUNUNITTESTS
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QFileInfo>
#include "statistics/statistics.h"
#include "system.h"
#include "mysimulator.h"
#include "datasource.h"
#include "nogui.h"
#include "GeometryLibrary/models/models.h"
int main(int argc, char *argv[])
{
    int GUI = true;
    if(argc > 1) {
        GUI = atoi(argv[1]);
    }

    qmlRegisterType<DataSource>("DataSource", 1, 0, "DataSource");
    qmlRegisterType<MySimulator>("MySimulator", 1, 0, "MySimulator");
    qmlRegisterType<System>("Diffusion", 1, 0, "System");
    qmlRegisterType<SystemProperties>("Diffusion", 1, 0, "SystemProperties");
    qmlRegisterType<MSDStatistic>("Diffusion",1,0,"MSDStatistic");
    qmlRegisterType<RegularNoiseModel>("GeometryLibrary", 1, 0, "RegularNoiseModel");
    qmlRegisterType<CylinderModel>("GeometryLibrary", 1, 0, "CylinderModel");
    qmlRegisterType<VoidModel>("GeometryLibrary", 1, 0, "VoidModel");
    qmlRegisterType<Octree>("GeometryLibrary", 1, 0, "OctreeModel");
    // qmlRegisterUncreatableType<Geometry>("Diffusion",1,0, "Geometry", "Abstract");
    qmlRegisterUncreatableType<Model>("GeometryLibrary",1,0, "Model", "Abstract");
    qmlRegisterUncreatableType<Statistic>("Diffusion",1,0, "Statistic", "Abstract");

    if(GUI==1) {
        qDebug() << "Running normal GUI mode";
        QApplication app(argc, argv);

        QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

        return app.exec();
    } else {
        QString iniFilename = QString("settings.ini");
        if(argc>2) {
            iniFilename = QString(argv[2]);
        }
        CIniFile iniFile;
        qDebug() << "Loading ini file: " << iniFilename;
        QFileInfo checkFile(iniFilename);
        if(!checkFile.exists()) {
            qDebug() << "Error, file " << iniFilename << " doesn't exist. Aborting!";
            return 0;
        }
        iniFile.load(iniFilename.toStdString());
        qDebug() << "Creating NoGUI object";
        NoGUI noGUI(&iniFile);
        if(GUI == 2) {
            qDebug() << "Creating visualizer";
            QApplication app(argc, argv);
            QQmlApplicationEngine engine;
            engine.load(QUrl(QStringLiteral("qrc:/main_nogui.qml")));
            MySimulator *simulator = nullptr;
            for(QObject *root : engine.rootObjects()) {
                for(QObject *p : root->children()) {
                    simulator = qobject_cast<MySimulator*>(p);
                    if(simulator) {
                        qDebug() << "Found simulator object.";
                        break;
                    }
                }
                if(simulator) break; // We found the child earlier.
            }

            simulator->setSystem(&noGUI.system);

            Octree *octree = qobject_cast<Octree*>(noGUI.system.properties()->model());
            if(octree) {
                qDebug() << "Enabling octree";
                simulator->setOctree(octree);
            }

            return app.exec();
        } else noGUI.run();
    }

    return 0;
}
#endif
