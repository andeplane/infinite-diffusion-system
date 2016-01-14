#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "geometry/geometries.h"
#include "system.h"
#include "mysimulator.h"
#include "figure.h"
#include "linegraph.h"
int main(int argc, char *argv[])
{
    qmlRegisterType<Figure>("QMLPlot", 1,0,"Figure");
    qmlRegisterType<LineGraph>("QMLPlot", 1,0,"LineGraph");
    qmlRegisterType<LineGraphDataSource>("QMLPlot", 1,0,"LineGraphDataSource");
    qmlRegisterType<MySimulator>("MySimulator", 1, 0, "MySimulator");
    qmlRegisterType<System>("Diffusion", 1, 0, "System");
    qmlRegisterType<SystemProperties>("Diffusion", 1, 0, "SystemProperties");
    qmlRegisterType<PerlinGeometry>("Diffusion", 1, 0, "PerlinGeometry");
    qmlRegisterType<CylinderGeometry>("Diffusion", 1, 0, "CylinderGeometry");
    qmlRegisterType<VoidGeometry>("Diffusion", 1, 0, "VoidGeometry");
    qmlRegisterUncreatableType<Geometry>("Diffusion",1,0, "Geometry", "Abstract");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

