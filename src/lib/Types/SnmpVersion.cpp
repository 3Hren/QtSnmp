#include "SnmpVersion.h"

SnmpVersion::SnmpVersion(Version version, QObject *parent) :
    Integer(static_cast<quint8>(version), parent)
{
}

SnmpVersion::Version SnmpVersion::getVersion() const
{
    return static_cast<Version>(getValue());
}
