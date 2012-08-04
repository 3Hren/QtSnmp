#include "GetRequestPDU.h"

GetRequestPDU::GetRequestPDU(QObject *parent) :
    ProtocolDataUnit(Type::GetRequestPDU, parent)
{
}

GetRequestPDU::GetRequestPDU(Integer *requestId, Integer *error, Integer *errorIndex, VarbindList *varbindList) :
    ProtocolDataUnit(Type::GetRequestPDU, requestId, error, errorIndex, varbindList)
{
}
