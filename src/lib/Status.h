#pragma once

class Status
{
public:
    enum Type {
        Ok = 0,
        NoResponseFromPeer = 1
    };

    Status();

    Type getType() const;

private:
    Type type;
};
