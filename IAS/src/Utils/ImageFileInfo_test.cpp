#include "ImageFileInfo.h"
#include "gtest/gtest.h"


class ImageFileInfoTest : public testing::Test
{
public:
    ImageFileInfoTest()
    {
        m_imageFileInfo = new ImageFileInfo("");
    }

protected:
    //Class Under Test
    ImageFileInfo* m_imageFileInfo;
    // Dependencias

};

TEST_F(ImageFileInfoTest, functionTest)
{
    m_imageFileInfo->bmpImageFullPath();
    m_imageFileInfo->loadBMPImage("");
    m_imageFileInfo->printImageFileInfo();
    m_imageFileInfo->size();
    m_imageFileInfo->width();
    m_imageFileInfo->height();
    m_imageFileInfo->timestampCreation();
    m_imageFileInfo->timestampLastMod();
    m_imageFileInfo->setBmpImageFullPath("/home/tesis/Repos/TESIS_V2/res/image.bmp");
    m_imageFileInfo->loadBMPImage("/home/tesis/Repos/TESIS_V2/res/image.bmp");
    m_imageFileInfo->printImageFileInfo();
    m_imageFileInfo->size();
    m_imageFileInfo->width();
    m_imageFileInfo->height();
    m_imageFileInfo->timestampCreation();
    m_imageFileInfo->timestampLastMod();
    m_imageFileInfo->setBmpImageFullPath("/home/tesis/Repos/TESIS_V2/res/image.jpg");
    m_imageFileInfo->loadBMPImage("/home/tesis/Repos/TESIS_V2/res/image.jpg");
    m_imageFileInfo->printImageFileInfo();
    m_imageFileInfo->size();
    m_imageFileInfo->width();
    m_imageFileInfo->height();
    m_imageFileInfo->timestampCreation();
    m_imageFileInfo->timestampLastMod();

}
