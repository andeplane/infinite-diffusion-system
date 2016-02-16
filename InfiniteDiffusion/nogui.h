#pragma once
#include "mysimulator.h"
#include "cinifile.h"
#include "geometrylibrary.h"
#include "system.h"
class NoGUI
{
private:
    CIniFile *m_iniFile;
    int m_timesteps;
    GeometryLibrary geometryLibrary;
    class Parameters *parameters = nullptr;
public:
    System system;

    NoGUI(CIniFile *iniFile);
    void run();
};
