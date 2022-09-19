//==========================================================================================================
// log.h - Defines a client mechanism for the logger
//==========================================================================================================
#pragma once
#include <string>
#include "udpsock.h"


//==========================================================================================================
// lookup_log_port() - Returns a UDP port number or -1
//
// Passed: file = Filename of the configuration file
//         spec = Fully qualified key-name.
//         tag  = The tag whose port number you wish to know.
//
// Returns: UDP port number or -1 to indicate failure
//==========================================================================================================
int lookup_log_port(const std::string file, const std::string key, const std::string tag);
//==========================================================================================================


//==========================================================================================================
// CLog() - The client side of the logging system
//==========================================================================================================
class CLog
{
public:

    ~CLog() {m_sock.close();}

    void    init(int port);

    void    print(const std::string& s);

    void    printf(const char* fmt, ...);

protected:

    UDPSock m_sock;
};
//==========================================================================================================
