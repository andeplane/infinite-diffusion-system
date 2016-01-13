#pragma once
#include <QVector3D>
class PerlinGeometry
{
public:
    class Properties {
        int octaves = 1;
        float persistence = 1.0;
        float sharpness = 1.0;
        bool abs = false;
        bool invert = false;
    };
private:
    Properties m_properties;

public:

    PerlinGeometry();
    bool pointIsVoid(const QVector3D &point);
    bool pointIsVoid(const float &x, const float &y, const float &z);
    Properties &properties() { return m_properties; }
};
