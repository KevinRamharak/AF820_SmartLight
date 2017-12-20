#include "Connection.h"

namespace AF820_SmartLight {
    namespace UDP {
        Connection::Connection(const char * address, uint16_t port) {
            this->address = std::string(address);
            this->port = port;
            this->connected = this->init();
        }

        Connection::Connection(std::string address, uint16_t port) {
            this->address = address;
            this->port = port;
            this->connected = this->init();
        }

        bool Connection::init() {
            this->socket_fd = socket(PF_INET, SOCK_DGRAM, 0);
            if(this->socket_fd < 0) {
                return false;
            }

            // setup endpoint address
            struct sockaddr_in endpoint = {0};
            endpoint.sin_family = AF_INET;
            endpoint.sin_addr.s_addr = inet_addr(this->address.c_str());
            endpoint.sin_port = htons(this->port);

            // enable broadcasting
            int opt = 1;
            setsockopt(this->socket_fd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

            // setup bind() call
            struct sockaddr_in my_addr = {0};
            my_addr.sin_family = AF_INET;
            my_addr.sin_addr.s_addr = INADDR_ANY;
            my_addr.sin_port = htons(0); // get random assigned port

            if(bind(this->socket_fd, (struct sockaddr *) &my_addr, sizeof(my_addr)) < 0) {
                close(this->socket_fd); // don't forget to free the file descriptor
                return false;
            }

            // #NOTE: This does not actually connect since UDP is connection less, but it does set a default endpoint for the send() and recv() calls
            if(connect(this->socket_fd, (struct sockaddr *) &endpoint, sizeof(endpoint)) < 0) {
                close(this->socket_fd); // don't forget to free the file descriptor
                return false;
            }

            // save these for now
            this->endpoint = endpoint;
            this->my_addr = my_addr;

            return true;
        }

        bool Connection::send(uint8_t * buffer, uint16_t len) {
            if(!this->connected) return false;
            int result = 0;

            do {
                result = ::send(this->socket_fd, &buffer[result], len - result, 0);
                if(result < 0) return false; // error
                if(result == 0) return false; // connection close :: can't happen with UDP right?
            } while(result != len);

            return true;
        }

        bool Connection::recv(uint8_t * buffer, uint16_t len) {
            if(!this->connected) return false;
            int result = 0;

            result = ::recv(this->socket_fd, buffer, len, 0);

            // 0 == connection closed
            // < 0 == error
            return result > 0;
        }
    }
}
