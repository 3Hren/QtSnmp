#pragma once

#include <QObject>
#include <QDataStream>
#include <QHash>

namespace Type{
enum AbstractSyntaxNotationOneType {
    Integer = 0x02,
    OctetString = 0x04,
    Null = 0x05,
    ObjectIdentifier = 0x06,
    Sequence = 0x30,
    GetRequestPDU = 0xa0,
    GetResponsePDU = 0xa2,

    NullObject = 0xff
};
}

typedef Type::AbstractSyntaxNotationOneType ASNType;

inline QDataStream &operator >>(QDataStream &inputStream, Type::AbstractSyntaxNotationOneType &type) {
    quint8 byte = 0;
    inputStream >> byte;
    type = static_cast<Type::AbstractSyntaxNotationOneType>(byte);
    return inputStream;
}
