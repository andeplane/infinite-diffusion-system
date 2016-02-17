#pragma once
#include "mysimulator.h"
#include "cinifile.h"
#include "system.h"
class NoGUI
{
private:
    CIniFile *m_iniFile;
    int m_timesteps;
public:
    SystemProperties systemProperties;
    System system;

    NoGUI(CIniFile *iniFile);
    void run();
};
