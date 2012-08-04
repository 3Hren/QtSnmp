#pragma once

#include "ProtocolDataUnit.h"

class GetRequestPDU : public ProtocolDataUnit
{
    Q_OBJECT
public:
    explicit GetRequestPDU(QObject *parent = 0);
    GetRequestPDU(Integer *requestId, Integer *error, Integer *errorIndex, VarbindList *varbindList);
};
