#pragma once

#include "AbstractSyntaxNotationOne.h"

//@Signed Integer32
class Integer : public AbstractSyntaxNotationOne
{
    Q_OBJECT
    qint32 value;
public:    
    Integer(QObject *parent = 0);
    Integer(qint32 value, QObject *parent = 0);

    qint32 getValue() const;

    QString toString() const;

private:
    quint8 getDataLength() const;
    QByteArray encodeData() const;
    void decodeData(QDataStream &inputStream, quint8 length);
};
