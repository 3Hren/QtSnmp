#include "AbstractSyntaxNotationOne.h"

#include "DataTypeFactory.h"

#include <QDataStream>

#include <QDebug>

static const quint8 TYPE_SIZE = 1;
static const quint8 LENGTH_SIZE = 1;

AbstractSyntaxNotationOne::AbstractSyntaxNotationOne(ASNType type, QObject *parent) :
    QObject(parent),
    type(type)
{
}

QByteArray AbstractSyntaxNotationOne::encode() const
{
    quint8 dataLength = getDataLength();

    QByteArray code;
    code.append(type);
    code.append(dataLength);
    code.append(encodeData());

    return code;
}

int AbstractSyntaxNotationOne::decode(QDataStream &inputStream)
{
    quint8 dataLength = 0;
    inputStream >> dataLength;
    decodeData(inputStream, dataLength);
    return LENGTH_SIZE + dataLength;
}

quint8 AbstractSyntaxNotationOne::getLength() const
{
    return TYPE_SIZE + LENGTH_SIZE + getDataLength();
}

Type::AbstractSyntaxNotationOneType AbstractSyntaxNotationOne::getType() const
{
    return type;
}

QString AbstractSyntaxNotationOne::toString() const
{
    return QString();
}
