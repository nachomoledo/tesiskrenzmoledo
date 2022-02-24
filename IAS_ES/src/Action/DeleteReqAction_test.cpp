#include "DeleteReqAction.h"
#include "gtest/gtest.h"


class DeleteReqActionTest : public testing::Test
{
public:
    DeleteReqActionTest()
    {
        m_imageDataBase = new ImageDataBase("", "");
        m_deleteReqAction = new DeleteReqAction(nullptr, m_imageList);
    }

protected:
    //Class Under Test
    DeleteReqAction* m_deleteReqAction;
    // Dependencias
    ImageDataBase *m_imageDataBase;
    QList<quint16> m_imageList;
};

TEST_F(DeleteReqActionTest, functionTest)
{
    m_deleteReqAction->execute();
    delete(m_deleteReqAction);
    m_deleteReqAction = new DeleteReqAction(m_imageDataBase, m_imageList);
    m_deleteReqAction->execute();
    delete(m_deleteReqAction);
    m_imageList.append(0);
    m_deleteReqAction = new DeleteReqAction(m_imageDataBase, m_imageList);
    m_deleteReqAction->execute();
    delete(m_deleteReqAction);
}
