#include "ImageEditor.h"
#include "gtest/gtest.h"


class ImageEditorTest : public testing::Test
{
public:
    ImageEditorTest()
    {

    }

protected:
    //Class Under Test
//    ImageEditor* m_imageEditor;
    // Dependencias

};

TEST_F(ImageEditorTest, functionTest)
{
    ImageEditor::selectROI("");
    ROI roi;
    ImageEditor::cropImage(0, "", {}, "");
    ImageEditor::cropImage(0, "", {roi}, "");
    ImageEditor::cropImage("", roi, "", "");

}
