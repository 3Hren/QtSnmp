#pragma once

#include <QObject>
#include <QStringList>

#include "Response.h"
#include "Status.h"

class QUdpSocket;
class SnmpMessage;
class Get : public QObject
{
    Q_OBJECT

    QString peer;
    QUdpSocket *socket;

    SnmpMessage *message;

    Response response;
    Status status;
public:
    Get(const QString &peer, const QString &objectId, const QString &community = QString("public"), QObject *parent = 0);

    void setTimeout(int msec = 1000);
    void setRetryCount(int retries = 3);

    void execute();
    Response getResponse() const;
    Status getStatus() const;

private Q_SLOTS:
    void readPendingDatagram();
};
