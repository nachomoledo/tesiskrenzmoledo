#include "KeepaliveCommandRes.h"
#include "Operators.h"

KeepaliveCommandRes::KeepaliveCommandRes(QByteArray catalogCheckSum)
{
    m_payload.append(catalogCheckSum);
}

CommandCode KeepaliveCommandRes::getCommandCode()
{
    return CommandCode::KEEPALIVE_RES;
}
