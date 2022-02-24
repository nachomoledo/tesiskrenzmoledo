#include "ErrorManager.h"

ErrorManager::ErrorManager(QObject *parent)
    : QObject(parent)
{
    setNames();
}

//bool ErrorManager::getErrorStatus() const
//{
//    return m_errorStatus;
//}

//void ErrorManager::setErrorStatus(bool errorStatus)
//{
//    m_errorStatus = errorStatus;
//}

void ErrorManager::setNames()
{
    m_errorNameMap.insert(ErrorId::NO_ERROR, "None");
    m_errorNameMap.insert(ErrorId::COMM_ERROR, "Comunication Error");
    m_errorNameMap.insert(ErrorId::UNKNOWN_ERROR, "Unknown Error");
}

void ErrorManager::setErrorMessage(ErrorId errorId, QString detail)
{
    if (m_errorNameMap.contains(errorId))
    {
        m_errorMessage = m_errorNameMap.value(errorId) + ": " + detail;
    }
    else
    {
        m_errorMessage = "Error " + QString::number(static_cast<int>(errorId)) + ": " + detail;
    }

    emit errorMessageChanged(m_errorMessage);
}
