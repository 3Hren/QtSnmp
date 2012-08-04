#pragma once

#include "Sequence.h"

#include <QList>

class Varbind;
class VarbindList : public Sequence
{
    Q_OBJECT
public:
    VarbindList(QObject *parent = 0);
    VarbindList(const SequenceData &sequenceData, QObject *parent = 0);

    QList<Varbind *> getVarbinds() const;
};
