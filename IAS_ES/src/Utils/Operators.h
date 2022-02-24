#ifndef OPERATORS_H
#define OPERATORS_H

#include <QByteArray>

QByteArray &operator<<(QByteArray &l, quint8 r);

QByteArray &operator<<(QByteArray &l, quint16 r);

QByteArray &operator<<(QByteArray &l, quint32 r);

QByteArray &operator<<(QByteArray &l, quint64 r);

#endif // OPERATORS_H
