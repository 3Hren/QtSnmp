#pragma once

#include <QObject>

#include "DataTypes.h"
#include "../Expections/SnmpException.h"

#include <QByteArray>

class DataTypeFactory;
class AbstractSyntaxNotationOne : public QObject
{
    Q_OBJECT
    Type::AbstractSyntaxNotationOneType type;
public:
    AbstractSyntaxNotationOne(ASNType type, QObject *parent = 0);

    QByteArray encode() const;
    int decode(QDataStream &inputStream);
    quint8 getLength() const;

    Type::AbstractSyntaxNotationOneType getType() const;

    virtual QString toString() const;

private:
    virtual quint8 getDataLength() const = 0;
    virtual QByteArray encodeData() const = 0;
    virtual void decodeData(QDataStream &inputStream, quint8 length) = 0;
};
