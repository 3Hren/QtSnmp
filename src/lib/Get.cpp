#include "Get.h"

#include "Types/DataTypeFactory.h"

#include "Types/ObjectIdentifier.h"
#include "Types/Null.h"

#include "Types/Sequence.h"
#include "Types/SnmpMessage.h"

#include "Types/SnmpVersion.h"
#include "Types/OctetString.h"

#include "Types/Varbind.h"
#include "Types/VarbindList.h"

#include "Types/GetRequestPDU.h"
#include "Types/GetResponsePDU.h"

#include <QUdpSocket>

#ifdef QT_SNMP_DEBUG
#include <QDebug>
#endif

Get::Get(const QString &peer, const QString &objectId, const QString &communityString, QObject *parent) :
    QObject(parent),    
    peer(peer),
    socket(new QUdpSocket(this))
{    
    socket->bind(10500);
    connect(socket,SIGNAL(readyRead()),SLOT(readPendingDatagram()));

    SnmpVersion *version = new SnmpVersion(SnmpVersion::SNMPv1);
    OctetString *community = new OctetString(communityString);    
    ProtocolDataUnit *getRequestPDU = new GetRequestPDU(objectId);
    message = new SnmpMessage(version, community, getRequestPDU, this);
}

void Get::setTimeout(int msec)
{
}

void Get::setRetryCount(int retries)
{
}

void Get::execute()
{        
    QByteArray datagram = message->encode();
    socket->writeDatagram(datagram, QHostAddress(peer), 161);
}

Response Get::getResponse() const
{
    return response;
}

Status Get::getStatus() const
{
}

void Get::readPendingDatagram()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QDataStream stream(&datagram, QIODevice::ReadOnly);
        Type::AbstractSyntaxNotationOneType type;
        stream >> type;

        if (type != Type::Sequence)
            throw SnmpException("Wrong response");

        quint8 bytesRead = 0;
        SnmpMessage sequence;
        bytesRead += sequence.decode(stream);

        QStringList responses;
        VarbindList *varbindList = sequence.getProtocolDataUnit()->getVarbindList();
        for (Varbind *varbind : varbindList->getVarbinds()) {
            responses += QString("%1 = %2 : %3")
                    .arg(varbind->getObjectIdentifier()->toString())
                    .arg(DataTypeFactory::getTypeName(varbind->getValue()->getType()))
                    .arg(varbind->getValue()->toString());

            AbstractSyntaxNotationOne *value = varbind->getValue();
            response.add(value->getType(), value->toString());
        }
    }
}
