#include "ImageDataBase.h"
#include "gtest/gtest.h"


class ImageDataBaseTest : public testing::Test
{
public:
    ImageDataBaseTest()
    {
        m_imageDataBase = new ImageDataBase("", "");
    }

protected:
    //Class Under Test
    ImageDataBase* m_imageDataBase;
    // Dependencias

};

TEST_F(ImageDataBaseTest, functionTest)
{
    void buildCatalog(void);
    m_imageDataBase->addImageToMap(0, "", "", "", 0);
    m_imageDataBase->addImageToMapAux(0, "", "", "", 0);
    m_imageDataBase->getImageName(0);
    m_imageDataBase->getImageNameWithExtension(0, "");
    m_imageDataBase->getImageDBPath();
    m_imageDataBase->getImageLQPath();
    m_imageDataBase->getImageHQPath();
    m_imageDataBase->getImageBasePathAndNameWithExtension(0, "");
    m_imageDataBase->loadCSVFile();
    m_imageDataBase->printDataBase();
    m_imageDataBase->registerImage(0, "", "", "", 0);
    m_imageDataBase->registerImage({});
    m_imageDataBase->getImageMap();
    m_imageDataBase->buildCatalogET(0, "", "", "", 0, 0, 0);
    m_imageDataBase->createCatalogBackup();
    m_imageDataBase->getImageMapAux();
    m_imageDataBase->deleteFromImageMap(0);
    m_imageDataBase->deleteFromImageMap({});
    m_imageDataBase->deleteFromCSVFile({});
    m_imageDataBase->deleteFromDisk(0);
    m_imageDataBase->checkExistingCSVFile();
    m_imageDataBase->getLastChecksum();
    m_imageDataBase->setImageMap({});
    m_imageDataBase->clearImageMapAux();
    m_imageDataBase->isDownloaded(0, "");
}
