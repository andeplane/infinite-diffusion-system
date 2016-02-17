#include "nogui.h"
#include "GeometryLibrary/models/models.h"

NoGUI::NoGUI(CIniFile *iniFile) :
    m_iniFile(iniFile)
{
    system.setProperties(&systemProperties);
    if(iniFile->find("model", "dtafile")) {
        // geometryLibrary.initialize();
    } else if(iniFile->find("model", "regular")) {
        Model *model = new RegularNoiseModel();
        model->loadParameters(iniFile);
        systemProperties.setModel(model);
    }
}

void NoGUI::run()
{
    SystemProperties systemProperties;
    // systemProperties.setGeometry();

}
