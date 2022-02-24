#include "DeleteReqAction.h"
#include <QDebug>

DeleteReqAction::DeleteReqAction(ImageDataBase *imageDataBase, QList<quint16> imageList)
    : m_imageDataBase(imageDataBase), m_imageList(imageList)
{

}

void DeleteReqAction::execute(void)
{
    //qDebug() << "begin DeleteReqAction::execute";
    if (m_imageDataBase)
    {
        m_imageDataBase->deleteFromCSVFile(m_imageList);
        for (int i = 0; i < m_imageList.size(); i++)
        {
            quint16 imageId = m_imageList.at(i);
            /* Importante borrar primero del disco y despues del mapa para obtener el nombre */
            m_imageDataBase->deleteFromDisk(imageId);
            m_imageDataBase->deleteFromImageMap(imageId);
        }
        m_imageDataBase->printDataBase();
    }

    //qDebug() << "end DeleteReqAction::execute";

}
