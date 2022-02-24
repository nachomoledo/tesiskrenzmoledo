#include "DeleteCommandReq.h"
#include "gtest/gtest.h"


class DeleteCommandReqTest : public testing::Test
{
public:
    DeleteCommandReqTest()
    {
        m_deleteCommandReq = new DeleteCommandReq({0});
    }

protected:
    //Class Under Test
    DeleteCommandReq* m_deleteCommandReq;
    // Dependencias

};

TEST_F(DeleteCommandReqTest, functionTest)
{
    m_deleteCommandReq->getCommandCode();
}
