#include "Response.h"

void Response::add(ASNType type, const QString &value)
{
    values.insert(type, value);
}

ASNType Response::getType(int pos) const
{
    return values.keys().at(pos);
}

QList<ASNType> Response::getTypes() const
{
    return values.keys();
}

QStringList Response::getValues(ASNType type) const
{
    return values.values(type);
}

QStringList Response::getValues() const
{
    return values.values();
}
