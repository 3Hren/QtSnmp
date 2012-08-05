#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>


#include "Types/Integer.h"
#include "Response.h"

#include "Get.h"

class QtSnmpLibTest : public QObject
{
    Q_OBJECT
    
public:
    QtSnmpLibTest();
    
private Q_SLOTS:
    void encodeInteger_data();
    void encodeInteger();

    void synchronousGet_data();
    void synchronousGet();
};

QtSnmpLibTest::QtSnmpLibTest()
{
    qWarning("Tests only works with my home notebook with snmp agent running");
}

void QtSnmpLibTest::encodeInteger_data()
{
    QTest::addColumn<qint32>("value");
    QTest::addColumn<QByteArray>("expected");

    QTest::newRow("+0       -> 02 01 00")               << +0        << QByteArray((const char[]){char(0x02), char(0x01), char(0x00)}, 3);
    QTest::newRow("+127     -> 02 01 7F")               << +127      << QByteArray((const char[]){char(0x02), char(0x01), char(0x7f)}, 3);
    QTest::newRow("-128     -> 02 01 80")               << -128      << QByteArray((const char[]){char(0x02), char(0x01), char(0x80)}, 3);
    QTest::newRow("+128     -> 02 02 00 80")            << +128      << QByteArray((const char[]){char(0x02), char(0x02), char(0x00), char(0x80)}, 4);
    QTest::newRow("+255     -> 02 02 00 ff")            << +255      << QByteArray((const char[]){char(0x02), char(0x02), char(0x00), char(0xff)}, 4);
    QTest::newRow("+256     -> 02 02 01 00")            << +256      << QByteArray((const char[]){char(0x02), char(0x02), char(0x01), char(0x00)}, 4);
    QTest::newRow("-129     -> 02 02 ff 7f")            << -129      << QByteArray((const char[]){char(0x02), char(0x02), char(0xff), char(0x7f)}, 4);
    QTest::newRow("32767    -> 02 02 7f ff")            << 32767     << QByteArray((const char[]){char(0x02), char(0x02), char(0x7f), char(0xff)}, 4);
    QTest::newRow("32768    -> 02 03 00 80 00")         << 32768     << QByteArray((const char[]){char(0x02), char(0x03), char(0x00), char(0x80), char(0x00)}, 5);
}

void QtSnmpLibTest::encodeInteger()
{
    QFETCH(qint32, value);
    QFETCH(QByteArray, expected);

    Integer integer(value);
    QCOMPARE(integer.encode(), expected);
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

    Response response = get.getResponse();
    QCOMPARE(response.getTypes().count(), 1);
    QCOMPARE(response.getType(0), Type::OctetString);
    QVERIFY(response.getValues(Type::OctetString).contains(expected));
}

QTEST_MAIN(QtSnmpLibTest)

#include "tst_qtsnmplibtest.moc"
