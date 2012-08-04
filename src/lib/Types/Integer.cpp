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

QString Integer::toString() const
{
    return QString::number(value);
}

quint8 Integer::getDataLength() const
{
    int value = this->value;
    int valueSize = 0;

    do {
        value >>= 7;
        valueSize++;
    } while (value != 0);

    return valueSize;
}

QByteArray Integer::encodeData() const
{    
    QByteArray code;

    int integer = value;
    int mask;
    int intsize = 4;

    /*
     * Truncate "unnecessary" bytes off of the most significant end of this
     * 2's complement integer.  There should be no sequence of 9
     * consecutive 1's or 0's at the most significant end of the
     * integer.
     */
    mask = 0x1FF << ((8 * 3) - 1);
    /* mask is 0xFF800000 on a big-endian machine */
    while ((((integer & mask) == 0) || ((integer & mask) == mask))
          && intsize > 1){
        intsize--;
        integer <<= 8;
    }
    //encodeHeader(os, type, intsize);
    mask = 0xFF << (8 * 3);
    /* mask is 0xFF000000 on a big-endian machine */
    while ((intsize--) > 0){
        code.append(((integer & mask) >> (8 * 3)));
        integer <<= 8;
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
