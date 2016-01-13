#include "system.h"

System::System()
{

}

void System::tick()
{

}

void System::setGeometry(Geometry *geometry)
{
    if (m_geometry == geometry)
        return;

    m_geometry = geometry;
    emit geometryChanged(geometry);
}

