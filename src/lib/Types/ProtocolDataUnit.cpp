#include "ProtocolDataUnit.h"

#include "Integer.h"
#include "VarbindList.h"

#include <QDebug>

ProtocolDataUnit::ProtocolDataUnit(Type::AbstractSyntaxNotationOneType type, QObject *parent) :
    AbstractSyntaxNotationOne(type, parent),
    requestId(new Integer(this)),
    error(new Integer(this)),
    errorIndex(new Integer(this)),
    varbindList(new VarbindList(this))
{
}

ProtocolDataUnit::ProtocolDataUnit(Type::AbstractSyntaxNotationOneType type, Integer *requestId, Integer *error, Integer *errorIndex, VarbindList *varbindList) : // #TODO: Make enum for "type"
    AbstractSyntaxNotationOne(type),
    requestId(requestId),
    error(error),
    errorIndex(errorIndex),
    varbindList(varbindList)
{
    requestId->setParent(this);
    error->setParent(this);
    errorIndex->setParent(this);
    varbindList->setParent(this);
}

Integer *ProtocolDataUnit::getRequestId() const
{
    return requestId;
}

Integer *ProtocolDataUnit::getError() const
{
    return error;
}

Integer *ProtocolDataUnit::getErrorIndex() const
{
    return errorIndex;
}

VarbindList *ProtocolDataUnit::getVarbindList() const
{
    return varbindList;
}

quint8 ProtocolDataUnit::getDataLength() const
{
    return requestId->getLength() + error->getLength() + errorIndex->getLength() + varbindList->getLength();
}

QByteArray ProtocolDataUnit::encodeData() const
{
    QByteArray code;
    code.append(requestId->encode());
    code.append(error->encode());
    code.append(errorIndex->encode());
    code.append(varbindList->encode());
    return code;
}

void ProtocolDataUnit::decodeData(QDataStream &inputStream, quint8 length)
{
    Q_UNUSED(length);

    quint8 requestIdType = 0;
    inputStream >> requestIdType;
    requestId->decode(inputStream);

    quint8 errorType = 0;
    inputStream >> errorType;
    error->decode(inputStream);

    quint8 errorIndexType = 0;
    inputStream >> errorIndexType;
    errorIndex->decode(inputStream);

    quint8 varbindListType = 0;
    inputStream >> varbindListType;
    varbindList->decode(inputStream);
}
