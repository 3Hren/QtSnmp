#include "GetRequestPDU.h"

#include "Integer.h"
#include "VarbindList.h"
#include "Null.h"

GetRequestPDU::GetRequestPDU(QObject *parent) :
    ProtocolDataUnit(Type::GetRequestPDU, parent)
{
}

GetRequestPDU::GetRequestPDU(const QString &objectIdentifierString, QObject *parent) :
    ProtocolDataUnit(Type::GetRequestPDU, parent)
{
    Null *value = new Null();
    varbindList->addVarbind(objectIdentifierString, value);
}
