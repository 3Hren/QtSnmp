#include "OctetString.h"

#include <QDataStream>

#include <QDebug>

OctetString::OctetString(QObject *parent) :
    AbstractSyntaxNotationOne(Type::OctetString, parent)
{
}

OctetString::OctetString(const QString &value, QObject *parent) :
    AbstractSyntaxNotationOne(Type::OctetString, parent),
    value(value)
{
}

QString OctetString::getValue() const
{
    return value;
}

QString OctetString::toString() const
{
    return getValue();
}

quint8 OctetString::getDataLength() const
{
    return value.length();
}

QByteArray OctetString::encodeData() const
{
    QByteArray code;
    code.append(value);
    return code;
}

void OctetString::decodeData(QDataStream &inputStream, quint8 length)
{
    quint8 bytesRead = 0;
    QByteArray buffer;

    while (bytesRead++ < length) {
        quint8 byte = 0;
        inputStream >> byte;
        buffer.append(byte);
    }

    value = buffer;
}
