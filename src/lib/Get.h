#pragma once

#include <QObject>
#include <QStringList>

class QUdpSocket;
class Get : public QObject
{
    Q_OBJECT

    QString peer;
    QString objectId;

    QUdpSocket *socket;

    QStringList response;
public:
    Get(const QString &peer, const QString &objectId, QObject *parent = 0);

    void execute();

    QStringList getResponse() const;

private Q_SLOTS:
    void readPendingDatagram();
};
