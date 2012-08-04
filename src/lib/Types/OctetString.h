#pragma once

#include "AbstractSyntaxNotationOne.h"
#include <QString>

class OctetString : public AbstractSyntaxNotationOne
{
    Q_OBJECT
    QString value;    
public:
    OctetString(QObject *parent = 0);
    OctetString(const QString &value, QObject *parent = 0);

    QString getValue() const;
    QString toString() const;

private:
    quint8 getDataLength() const;
    QByteArray encodeData() const;
    void decodeData(QDataStream &inputStream, quint8 length);
};
