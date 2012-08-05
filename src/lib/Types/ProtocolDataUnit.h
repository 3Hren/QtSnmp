#pragma once

#include "AbstractSyntaxNotationOne.h"

class Integer;
class VarbindList;
// #NOTE: True, but it would be ideally if Sequence be parent class.
class ProtocolDataUnit : public AbstractSyntaxNotationOne
{
    Q_OBJECT    
public:
    ProtocolDataUnit(Type::AbstractSyntaxNotationOneType type, QObject *parent = 0);

    Integer *getRequestId() const;
    Integer *getError() const;
    Integer *getErrorIndex() const;
    VarbindList *getVarbindList() const;

protected:
    Integer *requestId;
    Integer *error;
    Integer *errorIndex;
    VarbindList *varbindList;

private:
    quint8 getDataLength() const;
    QByteArray encodeData() const;
    void decodeData(QDataStream &inputStream, quint8 length);
};
