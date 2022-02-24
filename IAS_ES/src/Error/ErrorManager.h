#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include "ErrorId.h"
#include <QObject>
#include <QString>
#include <QMap>

class ErrorManager : public QObject
{
    Q_OBJECT
private:
//    bool m_errorStatus;
    QString m_errorMessage;
    QMap<ErrorId, QString> m_errorNameMap;
    void setNames(void);

public:
    ErrorManager(QObject *parent = nullptr);
    void setErrorMessage(ErrorId errorId, QString detail = "");

//    bool getErrorStatus() const;
//    void setErrorStatus(bool errorStatus);

signals:
    void errorMessageChanged(QString errorMessage);
};

#endif // ERRORMANAGER_H
