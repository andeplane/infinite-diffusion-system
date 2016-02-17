#include "nogui.h"
#include "GeometryLibrary/models/models.h"
#include "GeometryLibrary/parameters.h"

NoGUI::NoGUI(CIniFile *iniFile) :
    m_iniFile(iniFile)
{
    system.setProperties(&systemProperties);
    if(iniFile->find("model", "dtafile")) {
        // geometryLibrary.initialize();
    } else if(iniFile->find("model", "regular")) {
        Model *model = new RegularNoiseModel();
        NoiseParameters *parameters = new NoiseParameters(iniFile->getdouble("octaves"), iniFile->getdouble("scale"), iniFile->getdouble("persistence"), iniFile->getdouble("threshold"), iniFile->getdouble("inverted"), iniFile->getdouble("seed"), iniFile->getdouble("absolute"));
        model->setParameters(parameters);
        systemProperties.setModel(model);
    }
}

void NoGUI::run()
{
    SystemProperties systemProperties;
    // systemProperties.setGeometry();

}
