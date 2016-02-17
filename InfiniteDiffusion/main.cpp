#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "statistics/statistics.h"
#include "system.h"
#include "mysimulator.h"
#include "datasource.h"
#include "nogui.h"

int main(int argc, char *argv[])
{
    bool GUI = true;
    if(argc > 1) {
        GUI = atoi(argv[1]);
    }
    if(GUI) {
        qmlRegisterType<DataSource>("DataSource", 1, 0, "DataSource");
        qmlRegisterType<MySimulator>("MySimulator", 1, 0, "MySimulator");
        qmlRegisterType<System>("Diffusion", 1, 0, "System");
        qmlRegisterType<SystemProperties>("Diffusion", 1, 0, "SystemProperties");
        qmlRegisterType<StatisticDiffusionDistribution>("Diffusion",1,0,"StatisticDiffusionDistribution");
        // qmlRegisterUncreatableType<Geometry>("Diffusion",1,0, "Geometry", "Abstract");
        qmlRegisterUncreatableType<Statistic>("Diffusion",1,0, "Statistic", "Abstract");

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
        iniFile.load(iniFilename.toStdString());
        NoGUI noGUI(&iniFile);
        noGUI.run();
    }
}

