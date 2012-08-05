#pragma once

#include <QObject>
#include <QStringList>

#include "Response.h"

class QUdpSocket;
class Get : public QObject
{
    Q_OBJECT

    QString peer;
    QString objectId;

    QUdpSocket *socket;

    Response response;
public:
    Get(const QString &peer, const QString &objectId, QObject *parent = 0);

    void execute();

    Response getResponse() const;

private Q_SLOTS:
    void readPendingDatagram();
};
