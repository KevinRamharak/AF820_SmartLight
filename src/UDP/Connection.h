#ifndef AF820_SMARTLIGHT_UDP_CONNECTION_H_
#define AF820_SMARTLIGHT_UDP_CONNECTION_H_

#include <string>

// needed for socket
#include <unistd.h> /* close() syscall */
#include <sys/types.h> /* system data type definitions */
#include <sys/socket.h> /* socket specific definitions */
#include <netinet/in.h> /* INET constants and stuff */
#include <arpa/inet.h> /* IP address conversion stuff */
#include <netdb.h>

namespace AF820_SmartLight {
    namespace UDP {
        class Connection {
        private:
            std::string address;
            uint16_t port;
            bool connected;
            int socket_fd;
            struct sockaddr_in my_addr, endpoint;

        protected:
            bool init();

        public:
            Connection(const char * address, uint16_t port);
            Connection(std::string address, uint16_t port);

            bool send(uint8_t * buffer, uint16_t len);
            bool recv(uint8_t * buffer, uint16_t len);
        };
    }
}

#endif // AF820_SMARTLIGHT_UDP_CONNECTION_H_
