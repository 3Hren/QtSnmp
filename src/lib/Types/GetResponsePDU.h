#pragma once

#include "ProtocolDataUnit.h"

class GetResponsePDU : public ProtocolDataUnit
{
    Q_OBJECT
public:
    explicit GetResponsePDU(QObject *parent = 0);
};
