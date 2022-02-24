#include "EarthStation.h"
#include "gtest/gtest.h"




class EarthStationTest : public testing::Test
{
public:
    EarthStationTest()
    {
        m_earthStation = new EarthStation("", "");
    }

protected:
    //Class Under Test
    EarthStation* m_earthStation;
    // Dependencias
//    ErrorManager *m_errorManager;
//    ImageManager *m_imageManager;
//    CommLinkMonitor *m_commLinkMonitor;
};

TEST_F(EarthStationTest, functionTest)
{

    m_earthStation->getImageManager();
    m_earthStation->getCommLinkMonitor();
    m_earthStation->getErrorManager();
}
