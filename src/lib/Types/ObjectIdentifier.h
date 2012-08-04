#pragma once

#include "AbstractSyntaxNotationOne.h"

#include <QVector>

class Integer;
class ObjectIdentifier : public AbstractSyntaxNotationOne
{
    Q_OBJECT
    QVector<quint32> objectIdentifiers;
public:
    ObjectIdentifier(QObject *parent = 0);
    ObjectIdentifier(const QString &objectIdentifier, QObject *parent = 0);

    QString toString() const;

private:
    quint8 getDataLength() const;
    QByteArray encodeData() const;
    void decodeData(QDataStream &inputStream, quint8 length);
};
