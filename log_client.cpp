//==========================================================================================================
// log.cpp - Implements a client mechanism for the logger
//==========================================================================================================
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "log_client.h"
#include "config_file.h"

using namespace std;


//==========================================================================================================
// lookup_log_port() - Roots around in the config file to find a UDP port number
//==========================================================================================================
static int lookup_log_port(const std::string file, const std::string key, const std::string tag)
{
    CConfigFile cf;
    CConfigScript cs;

    // Open the config file, and tell the caller if we can't
    if (!cf.read(file, false)) return -1;

    // If the specified key doesn't exist in the config file, tell the caller
    if (!cf.exists(key)) return -1;

    // Fetch the list of tag/port pairs
    cf.get(key, &cs);

    // Search through that script spec for a matching tag
    while (cs.get_next_line())
    {
        string token = cs.get_next_token();
        int    port  = cs.get_next_int();

        if (strcasecmp(tag.c_str(), token.c_str()) == 0) return port;
    }

    // If we don't find a matching tag, tell the caller
    return -1;
}
//==========================================================================================================



//==========================================================================================================
// init() - Creates the sender socket
//==========================================================================================================
bool CLog::init(int port)
{
    return m_sock.create_sender(port, "localhost");
}
//==========================================================================================================


//==========================================================================================================
// init() - Looks up the appropriate UDP port and creates the sender socket
//==========================================================================================================
bool CLog::init(const std::string file, const std::string key, const std::string tag)
{
    // Lookup the UDP port associated with this tag
    int port = lookup_log_port(file, key, tag);

    // If we couldn't find it, tell the caller
    if (port < 0) return false;

    // And create a sender-socket for this port
    return init(port);
}
//==========================================================================================================



//==========================================================================================================
// print() - Logs a single string
//==========================================================================================================
void CLog::print(const string& s)
{
    m_sock.send(s.c_str(), s.length() + 1);    
}
//==========================================================================================================


//==========================================================================================================
// printf() - Logs printf-style data
//==========================================================================================================
void CLog::printf(const char* fmt, ...)
{
    char buffer[1024];

    // This is a pointer to the variable argument list
    va_list ap;

    // Point to the first argument after the "fmt" parameter
    va_start(ap, fmt);

    // Perform a printf of our arguments into a buffer area;
    vsnprintf(buffer, sizeof buffer, fmt, ap);

    // Tell the system that we're done with the "ap"
    va_end(ap);

    // And send the buffer
    m_sock.send(buffer, strlen(buffer) + 1);
}
//==========================================================================================================
