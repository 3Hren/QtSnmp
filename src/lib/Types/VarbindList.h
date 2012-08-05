#pragma once

#include "Sequence.h"

#include <QList>

class Varbind;
class VarbindList : public Sequence
{
    Q_OBJECT
public:
    explicit VarbindList(QObject *parent = 0);

    void addVarbind(const QString &objectIdentifierString, AbstractSyntaxNotationOne *value);
    QList<Varbind *> getVarbinds() const;
};
