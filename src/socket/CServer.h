#pragma once

#include "CSocketSession.h"

class CServer : public CSocketSession
{
public:

    bool start(const char* ip, int port);
    static void *makeThread(void* data);
};