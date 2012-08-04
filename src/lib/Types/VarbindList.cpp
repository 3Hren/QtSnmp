#include "VarbindList.h"

#include "Varbind.h"

VarbindList::VarbindList(QObject *parent) :
    Sequence(parent)
{
}

VarbindList::VarbindList(const SequenceData &sequenceData, QObject *parent) :
    Sequence(sequenceData, parent)
{
}

QList<Varbind *> VarbindList::getVarbinds() const
{
    QList<Varbind *> varbinds;
    for (AbstractSyntaxNotationOne *asnData : getSequenceData())
        varbinds << static_cast<Varbind *>(asnData);

    return varbinds;
}
