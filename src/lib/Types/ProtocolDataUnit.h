#pragma once

#include "AbstractSyntaxNotationOne.h"

class Integer;
class VarbindList;
// #NOTE: True, but it would be ideally if Sequence be parent class.
class ProtocolDataUnit : public AbstractSyntaxNotationOne
{
    Q_OBJECT
    Integer *requestId;
    Integer *error;
    Integer *errorIndex;
    VarbindList *varbindList;
public:
    ProtocolDataUnit(Type::AbstractSyntaxNotationOneType type, QObject *parent = 0);
    ProtocolDataUnit(Type::AbstractSyntaxNotationOneType type, Integer *requestId, Integer *error, Integer *errorIndex, VarbindList *varbindList);

    Integer *getRequestId() const;
    Integer *getError() const;
    Integer *getErrorIndex() const;
    VarbindList *getVarbindList() const;

private:
    quint8 getDataLength() const;
    QByteArray encodeData() const;
    void decodeData(QDataStream &inputStream, quint8 length);
};
