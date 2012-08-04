#pragma once

#include "DataTypes.h"

class QObject;
class AbstractSyntaxNotationOne;
class DataTypeFactory
{    
    typedef QHash<Type::AbstractSyntaxNotationOneType, QString> TypeMap;
    static TypeMap typeMap();
public:
    DataTypeFactory();

    static AbstractSyntaxNotationOne *createType(Type::AbstractSyntaxNotationOneType type, QObject *parent = 0);   
    static QString getTypeName(Type::AbstractSyntaxNotationOneType type);
};
