#pragma once

#include "Sequence.h"

class SnmpVersion;
class OctetString;
class ProtocolDataUnit;
class SnmpMessage : public Sequence
{
    Q_OBJECT
public:
    SnmpMessage(QObject *parent = 0);
    SnmpMessage(SnmpVersion *version, OctetString *community, ProtocolDataUnit *protocolDataUnit, QObject *parent = 0);

    SnmpVersion *getSnmpVersion() const;
    OctetString *getCommunity() const;
    ProtocolDataUnit *getProtocolDataUnit() const;
};
