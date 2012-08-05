#include "ObjectIdentifier.h"

#include "Integer.h"

#include <QStringList>

#include <QDebug>

#define HIGH_BIT 0x80

ObjectIdentifier::ObjectIdentifier(QObject *parent) :
    AbstractSyntaxNotationOne(Type::ObjectIdentifier, parent)
{
}

ObjectIdentifier::ObjectIdentifier(const QString &objectIdentifier, QObject *parent) :
    AbstractSyntaxNotationOne(Type::ObjectIdentifier, parent)
{        
    QStringList objectIdentifierStringList = objectIdentifier.split(".");
    objectIdentifierStringList.removeAll("");

    foreach (const QString &objectIdentifierStringValue, objectIdentifierStringList)
        objectIdentifiers.append(objectIdentifierStringValue.toInt());
}

QString ObjectIdentifier::toString() const
{
    QStringList objectIdentifierStringList;
    for (qint32 objectIdentifier : objectIdentifiers)
        objectIdentifierStringList += QString::number(objectIdentifier);

    return objectIdentifierStringList.join(".");
}

quint8 ObjectIdentifier::getDataLength() const
{
    quint8 totalLength = 1;

    for (int i = 2; i < objectIdentifiers.size(); ++i) {
        if (objectIdentifiers.at(i) < 128)
            totalLength += 1;
        else if (objectIdentifiers.at(i) < 2048)
            totalLength += 2;
        else if (objectIdentifiers.at(i) < 32768)
            totalLength += 3;
        else
            totalLength +=4;
    }

    return totalLength;
}

QByteArray ObjectIdentifier::encodeData() const
{
    if (objectIdentifiers.count() < 2)
        Q_ASSERT(false);//#TODO: throw Exception::SnmpException("Invalid Object Identifier");

    QByteArray code;
    code.append((quint8)(objectIdentifiers.at(0) * 40 + objectIdentifiers.at(1)));

    for (int i = 2; i < objectIdentifiers.size(); ++i) {
        QByteArray result;
        QByteArray tmp;
        quint32 value = objectIdentifiers.at(i);

        if (value < 128) { //#TODO: Magic
            result.append(value);
        } else {
            qint32 val = value;

            while (val != 0) {
                qint8 bval = (qint8)(val & 0xFF); //#TODO: Magic
                if ((bval & HIGH_BIT) != 0) {
                    bval = (qint8)(bval & ~HIGH_BIT);
                }

                val >>= 7;
                tmp.append(bval);
            }

            // Now we need to reverse the bytes for the final encoding
            for (int i = tmp.length() - 1; i >= 0; i--) {
                if (i > 0)
                    result.append(tmp[i] | HIGH_BIT);
                else
                    result.append(tmp[i]);
            }
        }

        code.append(result);
    }    

    return code;
}

void ObjectIdentifier::decodeData(QDataStream &inputStream, quint8 length)
{
    quint8 byte = 0;
    inputStream >> byte;

    objectIdentifiers.append(byte / 40);
    objectIdentifiers.append(byte % 40);

    quint8 bytesRead = 1;
    while (bytesRead++ < length) {
        quint8 buffer = 0;
        quint32 value = 0;
        inputStream >> buffer;

        if ((buffer & HIGH_BIT) == 0) {
            value = buffer;
        } else {
            QByteArray tmp;
            forever {
                tmp.append(buffer & ~HIGH_BIT);
                if ((buffer & HIGH_BIT) == 0)
                    break;

                inputStream >> buffer;
                bytesRead++;
            }

            for (int i = 0; i < tmp.size(); i++) {
                value <<= 7;
                value |= tmp[i];
            }
        }

        objectIdentifiers.append(value);
    }
}
