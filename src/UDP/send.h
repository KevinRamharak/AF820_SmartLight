#ifndef AF820_SMARTLIGHT_UDP_SEND_H_
#define AF820_SMARTLIGHT_UDP_SEND_H_

#include <string>

// needed for socket
#include <sys/types.h> /* system data type definitions */
#include <sys/socket.h> /* socket specific definitions */
#include <netinet/in.h> /* INET constants and stuff */
#include <arpa/inet.h> /* IP address conversion stuff */
#include <netdb.h>

namespace AF820_SmartLight {
    namespace UDP {
        // #NOTE: Only support IPv4, because really don't care about IPv6 for now
        bool send(const char * address, uint16_t port, uint8_t * pointer, uint16_t length);
        bool send(std::string address, uint16_t port, uint8_t * pointer, uint16_t length);
    }
}

#endif // AF820_SMARTLIGHT_UDP_SEND_H_
