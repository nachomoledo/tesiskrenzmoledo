#include "Files.h"

QStringList Files::processLine(QByteArray line)
{
    QStringList list;
    QList<QByteArray> subarrays;
    QByteArray trimmedLine = line.split('\r').first();
    subarrays = trimmedLine.split(',');
    for (int i = 0; i < subarrays.size(); i++)
    {
        list.append(subarrays.at(i));
    }
    return list;
}
