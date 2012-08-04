#pragma once

#include <exception>
#include <QString>

class SnmpException : public std::exception
{
    const char *reason;
public:
    SnmpException(const QString &reason) throw() :
        reason(reason.toLocal8Bit().constData())
    {
    }


    const char *what() const throw() {
        return reason;
    }
};
