#ifndef AF820_SMARTLIGHT_PROTOCOL_STANDARD_H_
#define AF820_SMARTLIGHT_PROTOCOL_STANDARD_H_

#include <cstdint>

#include "../UDP/send.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        // @NOTE(kevin@ramharak.nl): This class should probably be virtual (/abstract).
        // Reason it is not is the virtual function table. (?) This increases the 'sizeof()' and im not sure if this is only the class itself or also any (child)instances
        // it might conflict with the assumption that the class is an internal memory representation of the protocol
        class Standard {
        protected:
            uint8_t header [2] { 0x55, 0xAA };
            uint8_t length [2] { 0x00, 0x25 };
            const uint8_t fix_1  [3] { 0x01, 0x00, 0x00 };
            uint8_t device_mac [8] {};
            const uint8_t fix_2 [3] {};
            uint8_t device_code = 0x00;
            uint8_t device_version = 0x00;
            uint8_t device_function = 0x00;
            const uint8_t type_big = 0x00;
            const uint8_t type_small = 0x00;
            uint8_t controller_mac [4] {};
            const uint8_t fix_3 [4] {};
            uint8_t sequence_number [2] { 0x00, 0x01 };
            uint8_t extra_data_length [2] {};
            const uint8_t fix_4 [2] {};

            // #NOTE: This is a bit playing with fire since we return a raw byte pointer to the instance in memory.
            //        We assume its byte layout is its fields/members in the order specified in the header with no padding bytes
            //        It might be required to pad out the packets ourselfs with zeroed out bytes.
            const uint8_t * getByteStream() const;

        public:
            Standard();

            void setRemote(bool isRemote);
            void setRemote(uint8_t isRemote);

            void setLength(const uint8_t length);
            void setLength(const uint8_t * length);
            void setLength(const uint16_t length);

            void setDeviceMac(const uint8_t * mac);
            void setDeviceMac(const uint64_t mac);

            void setDeviceCode(const uint8_t code);

            void setDeviceFunction(const uint8_t func);
            void setDeviceFunction(const DeviceFunction func);

            void setControllerMac(const uint8_t * mac);
            void setControllerMac(const uint64_t mac);

            void setSequenceNumber(const uint8_t number);
            void setSequenceNumber(const uint8_t * number);
            void setSequenceNumber(const uint16_t number);

            uint16_t incrementSequenceNumber();

            void setExtraDataLength(const uint8_t length);
            void setExtraDataLength(const uint8_t * length);
            void setExtraDataLength(const uint16_t length);

            uint16_t copy(uint8_t * buffer, uint16_t buffer_length);// returns amount of bytes copied into the buffer
            /*
                Example use of 'copy()':
                {
                    // @TODO(kevin@ramahrak.nl) : Maybe use 'std::*_ptr<Protocol::Standard>' or something
                    Protocol::Standard * p = new Protocol::Standard();

                    // zeroed out tough it should not make a difference when sending UDP packets
                    // since the data the bulb cares about only reads till specified length
                    // and the user can use the return value to make sure only the bytes we care about will be send
                    char stack_buffer[1000] {};
                    uint16_t bytes_written = p->copy(stack_buffer, 1000); //  @NOTE(kevin@ramharak.nl): does 'stack_buffer' automatically decay to a pointer? or do i need to & it up?

                    // or more dynamic
                    uint16_t len = p->getLength();
                    char * heap_buffer = new char[len];
                    bytes_written = p->copy(heap_buffer, len);

                    // don't forget to delete the instance when you dont need it
                    delete p;

                    // ... use buffer in program

                    // and delete when done with it
                    delete[] heap_buffer;
                }

            */

            uint16_t getLength() const;
            uint16_t getExtraDataLength() const;

        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_STANDARD_H_
