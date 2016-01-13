#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "geometry/geometries.h"
#include "mysimulator.h"
int main(int argc, char *argv[])
{
    qmlRegisterType<MySimulator>("MySimulator", 1, 0, "MySimulator");
    qmlRegisterType<PerlinGeometry>("Diffusion", 1, 0, "PerlinGeometry");
    qmlRegisterType<CylinderGeometry>("Diffusion", 1, 0, "CylinderGeometry");
    qmlRegisterUncreatableType<Geometry>("Diffusion",1,0, "Geometry", "Abstract");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

