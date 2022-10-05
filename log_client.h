//==========================================================================================================
// log.h - Defines a client mechanism for the logger
//==========================================================================================================
#pragma once
#include <string>
#include "udpsock.h"

//==========================================================================================================
// CLog() - The client side of the logging system
//
// You should either declare a default tag when you call init(), or you should use the version of the
// logging APIs that require a tag to be explicitly passed.
//==========================================================================================================
class CLog
{
public:

    ~CLog() {m_sock.close();}

    // Call "init()" once at program startup
    bool    init(int port, const std::string& default_tag = "");

    // Logging API's that use the default tag
    void    print(const std::string& s);
    void    printf(const char* fmt, ...);

    // Logging API's that require an explicit tag
    void    xprint(const std::string& tag, const std::string& s);
    void    xprintf(const std::string& tag, const char* fmt, ...);

protected:

    std::string  m_default_tag;
    UDPSock      m_sock;
};
//==========================================================================================================
