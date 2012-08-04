#include "Varbind.h"

#include "ObjectIdentifier.h"

#include <QDebug>

Varbind::Varbind(ObjectIdentifier *objectIdentifier, AbstractSyntaxNotationOne *value, QObject *parent) :
    Sequence({objectIdentifier, value}, parent)
{
}

ObjectIdentifier *Varbind::getObjectIdentifier() const
{
    return static_cast<ObjectIdentifier *>(getDataType(0));
}

AbstractSyntaxNotationOne *Varbind::getValue() const
{
    return getDataType(1);
}
