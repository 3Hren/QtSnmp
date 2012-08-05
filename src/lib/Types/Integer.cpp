#include "Integer.h"

#include <QDataStream>

#ifdef QT_SNMP_DEBUG
#include <QDebug>
#endif

#define HIGH_BIT 0x80

Integer::Integer(QObject *parent) :
    AbstractSyntaxNotationOne(Type::Integer, parent),
    value(0)
{
}

Integer::Integer(qint32 value, QObject *parent) :
    AbstractSyntaxNotationOne(Type::Integer, parent),
    value(value)
{
}

qint32 Integer::getValue() const
{
    return value;
}

void Integer::setValue(qint32 value)
{
    this->value = value;
}

QString Integer::toString() const
{
    return QString::number(value);
}

quint8 Integer::getDataLength() const
{
    qint32 value = this->value;
    int mask = 0x01ff << ((8 * 3) - 1);

    int intSize = 4;
    while ((((value & mask) == 0) || ((value & mask) == mask)) && intSize > 1) {
        intSize--;
        value <<= 8;
    }

    return intSize;
}

QByteArray Integer::encodeData() const
{
    qint32 value = this->value;
    int mask;
    int intSize = 4;

    mask = 0x01ff << ((8 * 3) - 1);
    while ((((value & mask) == 0) || ((value & mask) == mask)) && intSize > 1) {
        intSize--;
        value <<= 8;
    }

    mask = 0xff << (8 * 3);

    QByteArray code;
    while ((intSize--) > 0) {
        code.append(((value & mask) >> (8 * 3)));
        value <<= 8;
    }

    return code;
}

void Integer::decodeData(QDataStream &inputStream, quint8 length)
{
    quint8 bytesRead = 0;

    quint8 byte = 0;
    inputStream >> byte;
    bytesRead++;

    value = (byte & HIGH_BIT) == 0 ? 0 : -1;

    forever {
        value <<= 8;
        value |= byte;

        if (bytesRead >= length)
            break;

        inputStream >> byte;
        bytesRead++;
    }
}
