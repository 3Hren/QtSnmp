#include "GetResponsePDU.h"

GetResponsePDU::GetResponsePDU(QObject *parent) :
    ProtocolDataUnit(Type::GetResponsePDU, parent)
{
}
