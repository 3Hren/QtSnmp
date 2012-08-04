#pragma once

#include "Sequence.h"

class ObjectIdentifier;
class Varbind : public Sequence
{
    Q_OBJECT
public:
    Varbind(ObjectIdentifier *objectIdentifier, AbstractSyntaxNotationOne *value, QObject *parent = 0);

    ObjectIdentifier *getObjectIdentifier() const;
    AbstractSyntaxNotationOne *getValue() const;
};
