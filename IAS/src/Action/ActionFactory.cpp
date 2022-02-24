#include "ActionFactory.h"
#include <QDebug>

ActionFactory::ActionFactory()
{

}

Action *ActionFactory::createAction(quint8 commandId, const QByteArray &packet)
{
    if (m_createActionFunctions.contains(commandId))
    {
        return m_createActionFunctions.value(commandId)(packet);
    }
    return nullptr;
}

void ActionFactory::registerCreateActionFn(quint8 commandID, createActionFn f)
{
    m_createActionFunctions.insert(commandID, f);
}
