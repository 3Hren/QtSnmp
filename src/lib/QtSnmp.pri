QT += network

HEADERS += \
    Types/AbstractSyntaxNotationOne.h \
    Types/Sequence.h \
    Types/SnmpMessage.h \
    Types/SnmpVersion.h \
    Types/Integer.h \
    Types/DataTypes.h \
    Types/OctetString.h \
    Types/ObjectIdentifier.h \
    Types/ProtocolDataUnit.h \
    Types/GetRequestPDU.h \
    Types/VarbindList.h \
    Types/Varbind.h \
    Types/Null.h \
    Types/DataTypeFactory.h \
    Types/GetResponsePDU.h \
    Expections/SnmpException.h \
    Types/NullObject.h \
    Get.h

SOURCES += \
    Types/AbstractSyntaxNotationOne.cpp \
    Types/Sequence.cpp \
    Types/SnmpMessage.cpp \
    Types/SnmpVersion.cpp \
    Types/Integer.cpp \
    Types/OctetString.cpp \
    Types/ObjectIdentifier.cpp \
    Types/ProtocolDataUnit.cpp \
    Types/GetRequestPDU.cpp \
    Types/VarbindList.cpp \
    Types/Varbind.cpp \
    Types/Null.cpp \
    Types/DataTypeFactory.cpp \
    Types/GetResponsePDU.cpp \
    Types/NullObject.cpp \
    Get.cpp
