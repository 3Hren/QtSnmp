#pragma once

#include "AbstractSyntaxNotationOne.h"

typedef QList<AbstractSyntaxNotationOne *> SequenceData;

class Sequence : public AbstractSyntaxNotationOne
{    
    Q_OBJECT
    SequenceData sequenceData;
public:
    Sequence(QObject *parent = 0);
    Sequence(const SequenceData &sequenceData, QObject *parent = 0);

    SequenceData getSequenceData() const;

protected:
    AbstractSyntaxNotationOne *getDataType(int pos) const;

private:
    quint8 getDataLength() const;
    QByteArray encodeData() const;
    void decodeData(QDataStream &inputStream, quint8 length);
};
