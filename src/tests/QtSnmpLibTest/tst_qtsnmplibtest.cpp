#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>


#include "Types/Integer.h"

#include "Get.h"

class QtSnmpLibTest : public QObject
{
    Q_OBJECT
    
public:
    QtSnmpLibTest();
    
private Q_SLOTS:
    void integerCoding_data();
    void integerCoding();

    void synchronousGet_data();
    void synchronousGet();
};

QtSnmpLibTest::QtSnmpLibTest()
{
    qWarning("Tests only works with my home notebook with snmp agent running");
}

void QtSnmpLibTest::integerCoding_data()
{
    QTest::addColumn<qint32>("value");
    QTest::addColumn<QByteArray>("expected");

    QTest::newRow("1 byte encoding & decoding") << (qint32)1 << (QByteArray().append(0x02).append(0x01).append(0x01));
    QTest::newRow("2 bytes encoding & decoding") << (qint32)2680 << (QByteArray().append(0x02).append(0x02).append(0x0A).append(0x78));
}

void QtSnmpLibTest::integerCoding()
{
    QFETCH(qint32, value);
    QFETCH(QByteArray, expected);

    Integer integer(value);
    QCOMPARE(integer.encode(), expected);

    Integer decodingInteger;
    QDataStream stream(&expected, QIODevice::ReadOnly);

    quint8 type = 0;
    stream >> type;
    decodingInteger.decode(stream);
    QCOMPARE(decodingInteger.getValue(), value);
}

void QtSnmpLibTest::synchronousGet_data()
{
    QTest::addColumn<QString>("peer");
    QTest::addColumn<QString>("objectId");
    QTest::addColumn<QString>("expected");

    QTest::newRow("Simple get") << "127.0.0.1" << ".1.3.6.1.2.1.1.4.0" << "Me <me@example.org>";
}

void QtSnmpLibTest::synchronousGet()
{
    QFETCH(QString, peer);
    QFETCH(QString, objectId);
    QFETCH(QString, expected);

    Get get(peer, objectId);
    get.execute();
    QTest::qWait(100);

    QVERIFY(get.getResponse().contains(expected));
}

QTEST_MAIN(QtSnmpLibTest)

#include "tst_qtsnmplibtest.moc"
