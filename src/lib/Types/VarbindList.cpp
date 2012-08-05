#include "VarbindList.h"

#include "Varbind.h"
#include "ObjectIdentifier.h"

VarbindList::VarbindList(QObject *parent) :
    Sequence(parent)
{
}

void VarbindList::addVarbind(const QString &objectIdentifierString, AbstractSyntaxNotationOne *value)
{
    ObjectIdentifier *objectIdentifier = new ObjectIdentifier(objectIdentifierString);
    Varbind *varbind = new Varbind(objectIdentifier, value);
    addSequenceData(varbind);
}

QList<Varbind *> VarbindList::getVarbinds() const
{
    QList<Varbind *> varbinds;
    for (AbstractSyntaxNotationOne *asnData : getSequenceData())
        varbinds << static_cast<Varbind *>(asnData);

    return varbinds;
}
