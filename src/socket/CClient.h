#pragma once
#include "CSocketSession.h"

class CClient : public CSocketSession
{
public:
    void Connect(const char* ip, int port);
};

