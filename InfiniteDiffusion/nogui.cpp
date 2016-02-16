#include "nogui.h"
#include "parameters.h"
#include "GeometryLibrary/models/regularparameters.h"
#include "GeometryLibrary/models/multifractalparameters.h"

NoGUI::NoGUI(CIniFile *iniFile) :
    m_iniFile(iniFile)
{
    if(iniFile->find("geometry", "dtafile")) {
        // geometryLibrary.initialize();

    } else if(iniFile->find("geometry", "regular")) {
        parameters = new RegularParameters(iniFile->getdouble("octaves"), iniFile->getdouble("scale"), iniFile->getdouble("persistence"), iniFile->getdouble("threshold"), iniFile->getdouble("inverted"), iniFile->getdouble("seed"), iniFile->getdouble("absolute"));
        if(iniFile->find("noisetype", "perlin")) {
            geometryLibrary.initialize(GeometryLibrary::Regular, Noise::Perlin, parameters);
        } else if(iniFile->find("noisetype", "simplex")) {
            geometryLibrary.initialize(GeometryLibrary::Regular, Noise::Simplex, parameters);
        }
    } else if(iniFile->find("geometry", "multifractal")) {
        parameters = new MultiFractalParameters(iniFile->getdouble("octaves"), iniFile->getdouble("scale"), iniFile->getdouble("persistence"), iniFile->getdouble("threshold"), iniFile->getdouble("inverted"), iniFile->getdouble("seed"), iniFile->getdouble("absolute"),
                                                iniFile->getdouble("lacunarity"), iniFile->getdouble("gain"), iniFile->getdouble("offset"));
        if(iniFile->find("noisetype", "perlin")) {
            geometryLibrary.initialize(GeometryLibrary::MultiFractal, Noise::Perlin, parameters);
        } else if(iniFile->find("noisetype", "simplex")) {
            geometryLibrary.initialize(GeometryLibrary::MultiFractal, Noise::Simplex, parameters);
        }
    }
}

void NoGUI::run()
{
    SystemProperties systemProperties;

}
