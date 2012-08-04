#include "DataTypeFactory.h"

#include "Integer.h"
#include "OctetString.h"
#include "Null.h"
#include "ObjectIdentifier.h"
#include "Sequence.h"
#include "GetRequestPDU.h"
#include "GetResponsePDU.h"

#include "NullObject.h"

#include <QDebug>

DataTypeFactory::DataTypeFactory()
{
}

DataTypeFactory::TypeMap DataTypeFactory::typeMap()
{
    static TypeMap typeMap;
    if (typeMap.isEmpty()) {
        typeMap.insert(Type::Integer, "Integer");
        typeMap.insert(Type::OctetString, "String");
        typeMap.insert(Type::NullObject, "Unknown type");
    }
    return typeMap;
}

AbstractSyntaxNotationOne *DataTypeFactory::createType(Type::AbstractSyntaxNotationOneType type, QObject *parent)
{
    switch (type) {
    case Type::Integer: return new Integer(parent);
    case Type::OctetString: return new OctetString(parent);
    case Type::Null: return new Null(parent);
    case Type::ObjectIdentifier: return new ObjectIdentifier(parent);
    case Type::Sequence: return new Sequence(parent);
    case Type::GetRequestPDU: return new GetRequestPDU(parent);
    case Type::GetResponsePDU: return new GetResponsePDU(parent);
    default:
        Q_ASSERT_X(false, "factory method", QString("Unknown type: %1").arg(type).toLatin1());
    };

    return NullObject::Instance();
}

QString DataTypeFactory::getTypeName(Type::AbstractSyntaxNotationOneType type)
{
    return typeMap().value(type);
}
