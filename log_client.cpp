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
// init() - Creates the sender socket
//==========================================================================================================
bool CLog::init(int port, const string& default_tag)
{
    m_default_tag = default_tag;
    return m_sock.create_sender(port, "localhost");
}
//==========================================================================================================


//==========================================================================================================
// print() - Logs a single string
//==========================================================================================================
void CLog::print(const string& s)
{
    print(m_default_tag, s);
}
//==========================================================================================================


//==========================================================================================================
// print() - Logs a single string
//==========================================================================================================
void CLog::print(const string& tag, const string& s)
{
    char buffer[1024];

    // Find out how long the tag is
    int length = tag.length();

    // Copy the tag into the buffer
    strncpy(buffer, tag.c_str(), length);

    // Point to the character after the tag
    char* p = buffer + length;

    // Append a '$' delimieter between the tag and the message
    *p++ = '$';

    // Copy the message into the buffer
    strcpy(p, s.c_str());

    // And send the entire buffer including the nul byte on the end
    m_sock.send(buffer, strlen(buffer) + 1);    
}
//==========================================================================================================



//==========================================================================================================
// printf() - Logs printf-style data
//==========================================================================================================
void CLog::printf(const char* fmt, ...)
{
    char buffer[1024];

    // This routine uses the default tag
    const string& tag = m_default_tag;

    // Get the length of the buffer
    int buffer_len = sizeof(buffer);

    // Find out how long the tag is
    int tag_length = tag.length();

    // Copy the tag into the buffer
    strncpy(buffer, tag.c_str(), tag_length);

    // Point to the character after the tag
    char* p = buffer + tag_length;

    // Append a '$' delimeter between the tag and the message
    *p++ = '$';

    // Keep track of the remaining buffer length
    buffer_len -= (tag_length + 1);

    // This is a pointer to the variable argument list
    va_list ap;

    // Point to the first argument after the "fmt" parameter
    va_start(ap, fmt);

    // Perform a printf of our arguments into a buffer area;
    vsnprintf(p, buffer_len, fmt, ap);

    // Tell the system that we're done with the "ap"
    va_end(ap);

    // And send the buffer
    m_sock.send(buffer, strlen(buffer) + 1);
}
//==========================================================================================================





//==========================================================================================================
// printf() - Logs printf-style data
//==========================================================================================================
void CLog::printf(const string& tag, const char* fmt, ...)
{
    char buffer[1024];

    // Get the length of the buffer
    int buffer_len = sizeof(buffer);

    // Find out how long the tag is
    int tag_length = tag.length();

    // Copy the tag into the buffer
    strncpy(buffer, tag.c_str(), tag_length);

    // Point to the character after the tag
    char* p = buffer + tag_length;

    // Append a '$' delimeter between the tag and the message
    *p++ = '$';

    // Keep track of the remaining buffer length
    buffer_len -= (tag_length + 1);

    // This is a pointer to the variable argument list
    va_list ap;

    // Point to the first argument after the "fmt" parameter
    va_start(ap, fmt);

    // Perform a printf of our arguments into a buffer area;
    vsnprintf(p, buffer_len, fmt, ap);

    // Tell the system that we're done with the "ap"
    va_end(ap);

    // And send the buffer
    m_sock.send(buffer, strlen(buffer) + 1);
}
//==========================================================================================================

