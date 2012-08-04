#pragma once

#include "Integer.h"

class SnmpVersion : public Integer
{
    Q_OBJECT
public:
    enum Version {
        SNMPv1 = 0
    };

    SnmpVersion(Version version, QObject *parent = 0);

    Version getVersion() const;
};
