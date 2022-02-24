#include "MainScreenViewModel.h"
#include "gtest/gtest.h"


class MainScreenViewModelTest : public testing::Test
{
public:
    MainScreenViewModelTest()
    {
        m_imageManager = new ImageManager(new TransmissionQueue(), new ImageDataBase("", ""), new ImageEditor());
        m_mainScreenViewModel = new MainScreenViewModel(m_imageManager);
    }

protected:
    //Class Under Test
    MainScreenViewModel* m_mainScreenViewModel;
    // Dependencias
    ImageManager *m_imageManager;
};

TEST_F(MainScreenViewModelTest, functionTest)
{
    m_mainScreenViewModel->getConnectButton();
    m_mainScreenViewModel->getCommStatus();
    m_mainScreenViewModel->getError();
    m_mainScreenViewModel->getLostMessages();
    m_mainScreenViewModel->getReceivedMesseges();
    m_mainScreenViewModel->getSentMesseges();
    m_mainScreenViewModel->getCatalog();
    m_mainScreenViewModel->setCatalog({});
    m_mainScreenViewModel->getCaptureButton();
    m_mainScreenViewModel->getUpdateCatalogButton();
    m_mainScreenViewModel->getSyncCatalogButton();
    m_mainScreenViewModel->getDownloadSamplesButton();
    m_mainScreenViewModel->getDownloadInHQButton();
    m_mainScreenViewModel->getDeleteButton();
    m_mainScreenViewModel->getCropButton();
    m_mainScreenViewModel->getSetLedOBCButton();
    m_mainScreenViewModel->getSetLedIASButton();
}
