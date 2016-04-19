#pragma once
#include <QObject>
#include <QElapsedTimer>
#include "mysimulator.h"
#include "GeometryLibrary/misc/cinifile.h"
#include "system.h"
class NoGUI
{
private:
    CIniFile *m_iniFile;
    int m_timesteps = 0;
    int m_currentTimestep = 0;
    QElapsedTimer timer;
public:
    System system;
    bool finished = false;

    NoGUI(CIniFile *iniFile);
    void run();
    Q_INVOKABLE bool tick();
};
