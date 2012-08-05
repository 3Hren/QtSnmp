#pragma once

#include "ProtocolDataUnit.h"

class GetRequestPDU : public ProtocolDataUnit
{
    Q_OBJECT
public:
    explicit GetRequestPDU(QObject *parent = 0);
    GetRequestPDU(const QString &objectIdentifierString, QObject *parent = 0);
};
