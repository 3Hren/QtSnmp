#pragma once

#include "Types/DataTypes.h"

#include <QMultiHash>
#include <QStringList>

class Response
{
    QMultiHash<ASNType, QString> values;
public:
    void add(ASNType type, const QString &value);

    ASNType getType(int pos) const;
    QList<ASNType> getTypes() const;

    QStringList getValues(ASNType type) const;
    QStringList getValues() const;
};
