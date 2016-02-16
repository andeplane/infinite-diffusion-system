#pragma once
#include <QObject>
#include <QVector3D>
#include <models/regularparameters.h>
#include <geometrylibrary.h>

class Geometry : public QObject
{
    Q_OBJECT
public:
    Geometry();
    bool pointIsVoid(const QVector3D &point);
    virtual bool pointIsVoid(const float &x, const float &y, const float &z) = 0;
};
