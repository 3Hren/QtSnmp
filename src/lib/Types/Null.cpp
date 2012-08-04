#include "Null.h"

Null::Null(QObject *parent) :
    AbstractSyntaxNotationOne(Type::Null, parent)
{
}

QString Null::toString() const
{
    return QString("null");
}

quint8 Null::getDataLength() const
{
    return 0;
}

QByteArray Null::encodeData() const
{
    return QByteArray();
}

void Null::decodeData(QDataStream &inputStream, quint8 length)
{
    Q_UNUSED(inputStream);
    Q_UNUSED(length);
}
