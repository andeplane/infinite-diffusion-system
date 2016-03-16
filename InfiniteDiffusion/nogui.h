#pragma once
#include "mysimulator.h"
#include "GeometryLibrary/misc/cinifile.h"
#include "system.h"
class NoGUI
{
private:
    CIniFile *m_iniFile;
    int m_timesteps;
public:
    System system;

    NoGUI(CIniFile *iniFile);
    void run();
};
