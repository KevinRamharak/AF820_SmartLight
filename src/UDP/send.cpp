#include "send.h"

namespace AF820_SmartLight {
    namespace UDP {
        bool send(const char * address, uint16_t port, uint8_t * pointer, uint16_t length) {
            if(length > 65507) { // UINT16_MAX - 8 byte header - 16 byte checksum
                return false; // packet to large
            }

            int socket_fd = socket(PF_INET, SOCK_DGRAM, 0);
            if(socket_fd < 0) {
                return false; // error opening socket
            }

            struct sockaddr_in endpoint = {0};
            endpoint.sin_family = AF_INET;
            endpoint.sin_addr.s_addr = inet_addr(address);
            endpoint.sin_port = htons(port);

            // dont forget to set broadcast option
            int opt = 1;
            setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

            int result = ::sendto(socket_fd, pointer, length, 0, (struct sockaddr *) &endpoint, sizeof(endpoint));

            if(result < 0) {
                return false; // error sending
            }

            return result == length; // if we did not send the length then the packet is unreliable
        }

        bool send(std::string address, uint16_t port, uint8_t * pointer, uint16_t length) {
            return UDP::send(address.c_str(), port, pointer, length);
        }
    }
}
