#include "SnmpMessage.h"

#include "SnmpVersion.h"
#include "OctetString.h"
#include "ProtocolDataUnit.h"

#ifdef QT_SNMP_DEBUG
#include <QDebug>
#endif

enum DataPosition {
    SnmpVersionPosition = 0,
    CommunityPosition = 1,
    ProtocolDataUnitPosition = 2
};

SnmpMessage::SnmpMessage(QObject *parent) :
    Sequence(parent)
{
}

SnmpMessage::SnmpMessage(SnmpVersion *version, OctetString *community, ProtocolDataUnit *protocolDataUnit, QObject *parent) :
    Sequence(SequenceData{version, community, protocolDataUnit}, parent)
{
}

SnmpVersion *SnmpMessage::getSnmpVersion() const
{
    return static_cast<SnmpVersion *>(getDataType(SnmpVersionPosition));
}

OctetString *SnmpMessage::getCommunity() const
{
    return static_cast<OctetString *>(getDataType(CommunityPosition));
}

ProtocolDataUnit *SnmpMessage::getProtocolDataUnit() const
{    
    return static_cast<ProtocolDataUnit *>(getDataType(ProtocolDataUnitPosition));
}
