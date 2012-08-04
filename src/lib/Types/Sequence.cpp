#include "Sequence.h"

#include "DataTypeFactory.h"
#include "NullObject.h"

#include <QDataStream>

#include <QDebug>

Sequence::Sequence(QObject *parent) :
    AbstractSyntaxNotationOne(Type::Sequence, parent)
{
}

Sequence::Sequence(const SequenceData &sequenceData, QObject *parent) :
    AbstractSyntaxNotationOne(Type::Sequence, parent),
    sequenceData(sequenceData)
{
    foreach (AbstractSyntaxNotationOne *data, sequenceData)
        data->setParent(this);
}

SequenceData Sequence::getSequenceData() const
{
    return sequenceData;
}

AbstractSyntaxNotationOne *Sequence::getDataType(int pos) const
{
    if (sequenceData.size() < pos + 1)
        throw SnmpException("No such element");
    return sequenceData.at(pos);
}

quint8 Sequence::getDataLength() const
{
    quint8 totalDataLength = 0;
    foreach (AbstractSyntaxNotationOne *value, sequenceData)
        totalDataLength += value->getLength();
    return totalDataLength;
}

QByteArray Sequence::encodeData() const
{
    QByteArray code;
    foreach (AbstractSyntaxNotationOne *value, sequenceData)
        code.append(value->encode());
    return code;
}

void Sequence::decodeData(QDataStream &inputStream, quint8 length)
{
    quint32 bytesRead = 0;
    while (!inputStream.atEnd() && bytesRead++ < length) {
        quint8 type = 0;
        inputStream >> type;
        AbstractSyntaxNotationOne *asnType = DataTypeFactory::createType(static_cast<Type::AbstractSyntaxNotationOneType>(type), this);
        bytesRead += asnType->decode(inputStream);

        sequenceData.append(asnType);
    }
}
