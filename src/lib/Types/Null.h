#pragma once

#include "AbstractSyntaxNotationOne.h"

class Null : public AbstractSyntaxNotationOne
{
    Q_OBJECT
public:
    Null(QObject *parent = 0);

    QString toString() const;

private:
    quint8 getDataLength() const;
    QByteArray encodeData() const;
    void decodeData(QDataStream &inputStream, quint8 length);
};
