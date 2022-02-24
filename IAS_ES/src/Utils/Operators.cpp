#include "Operators.h"

QByteArray &operator<<(QByteArray &l, quint8 r)
{
    l.append(r);
    return l;
}

QByteArray &operator<<(QByteArray &l, quint16 r)
{
    return l<<quint8(r>>8)<<quint8(r);
}

QByteArray &operator<<(QByteArray &l, quint32 r)
{
    return l<<quint16(r>>16)<<quint16(r);
}

QByteArray &operator<<(QByteArray &l, quint64 r)
{
    return l<<quint32(r>>32)<<quint32(r);
}
