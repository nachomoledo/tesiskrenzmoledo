#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "Action.h"
#include <QHash>
#include <functional>
//https://stackoverflow.com/questions/28746744/passing-capturing-lambda-as-function-pointer
class ActionFactory
{
protected:
    using createActionFn = std::function<Action*(const QByteArray &packet)>;

private:
    QHash<quint8, createActionFn> m_createActionFunctions;

protected:
   void registerCreateActionFn(quint8 commandID, createActionFn f);

public:   
    ActionFactory();
    Action *createAction(quint8 commandId, const QByteArray &packet);

};

#endif // ACTIONFACTORY_H
