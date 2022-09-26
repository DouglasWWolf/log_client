//==========================================================================================================
// log.h - Defines a client mechanism for the logger
//==========================================================================================================
#pragma once
#include <string>
#include "udpsock.h"

//==========================================================================================================
// CLog() - The client side of the logging system
//==========================================================================================================
class CLog
{
public:

    ~CLog() {m_sock.close();}

    bool    init(int port);

    bool    init(const std::string file, const std::string key, const std::string tag);

    void    print(const std::string& s);

    void    printf(const char* fmt, ...);

protected:

    UDPSock m_sock;
};
//==========================================================================================================
