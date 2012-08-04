#pragma once

#include "AbstractSyntaxNotationOne.h"

class NullObject : public AbstractSyntaxNotationOne
{
    Q_OBJECT
public: 
    QString toString() const;

    static NullObject *Instance();
private:
    NullObject(QObject *parent = 0);

    quint8 getDataLength() const;
    QByteArray encodeData() const;
    void decodeData(QDataStream &inputStream, quint8 length);
};
