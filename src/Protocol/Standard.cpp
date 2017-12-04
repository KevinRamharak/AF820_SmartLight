#include "Standard.h"

namespace AF820_SmartLight {
    namespace Protocol {
        Standard::Standard() {}

        void Standard::setRemote(bool isRemote) {
            this->header[1] = isRemote ? 0x66 : 0xAA;
        }

        void Standard::setRemote(uint8_t isRemote) {
            this->header[1] = isRemote > 0 ? 0x66 : 0xAA;
        }

        void Standard::setLength(const uint8_t length) {
            this->length[0] = 0x00;
            this->length[1] = length;
        }
        void Standard::setLength(const uint8_t * length) {
            this->length[0] = length[0];
            this->length[1] = length[1];
        }
        void Standard::setLength(const uint16_t length) {
            this->length[0] = (uint8_t) (length >> 8);
            this->length[1] = (uint8_t) length;
        }

        // destination mac is really weird
        // lamp 1
        // actual mac = 0x62, 0x01, 0x94 ,0x14, 0xB4, 0xC6
        // dest_mac = 0x00, 0x00, 0x00, 0x00, 0xc6, 0xb4, 0x14, 0x00
        void Standard::setDeviceMac(const uint8_t * mac) {
            for(uint8_t i = 0; i < 6; i++) {
                this->device_mac[i + 2] = mac[i];
            }
        }
        void Standard::setDeviceMac(const uint64_t mac) {
            // if you forgot how this works unroll the loop
            for(uint8_t i = 0; i < 6; i++) {
                this->device_mac[i + 2] = (uint8_t) (mac >> (56 - i * 8) );
            }
        }

        void Standard::setDeviceCode(const uint8_t code) {
            this->device_code = code;
        }

        void Standard::setDeviceFunction(const uint8_t func) {
            this->device_function = func;
        }
        void Standard::setDeviceFunction(const DeviceFunction func) {
            this->device_function = (uint8_t) func;
        }

        void Standard::setControllerMac(const uint8_t * mac) {
            for(uint8_t i = 0; i < 6; i++) {
                this->controller_mac[i + 2] = mac[i];
            }
        }
        void Standard::setControllerMac(const uint64_t mac) {
            // if you forgot how this works unroll the loop
            for(uint8_t i = 0; i < 6; i++) {
                this->controller_mac[i + 2] = (uint8_t) (mac >> (56 - i * 8) );
            }
        }

        void Standard::setSequenceNumber(const uint8_t number) {
            this->sequence_number[0] = 0x00;
            this->sequence_number[1] = number;
        }
        void Standard::setSequenceNumber(const uint8_t * number) {
            this->sequence_number[0] = number[0];
            this->sequence_number[1] = number[1];
        }
        void Standard::setSequenceNumber(const uint16_t number) {
            this->sequence_number[0] = (uint8_t) (number >> 8);
            this->sequence_number[1] = (uint8_t) number;
        }

        uint16_t Standard::incrementSequenceNumber() {
            // https://gitlab.com/iot/af820smartlight#protocol
            // A monotonically increasing sequence number for each packet.
            // It is never zero.
            this->sequence_number[1]++;
            if(this->sequence_number[1] == 0) {
                this->sequence_number[0]++;
                // if [1] wrapped and [0] wrapped they will both be 0 -> since it can never be 0 we increment [1] again
                if(this->sequence_number[0] == 0) {
                    this->sequence_number[1] = 1;
                }
            }

            return (uint16_t) (this->sequence_number[0] << 8) + this->sequence_number[1];
        }

        void Standard::setExtraDataLength(const uint8_t length) {
            this->extra_data_length[0] = 0x00;
            this->extra_data_length[1] = length;
        }
        void Standard::setExtraDataLength(const uint8_t * length) {
            this->extra_data_length[0] = length[0];
            this->extra_data_length[1] = length[1];
        }
        void Standard::setExtraDataLength(const uint16_t length) {
            this->extra_data_length[0] = (uint8_t) (length >> 8);
            this->extra_data_length[1] = (uint8_t) length;
        }

        uint16_t Standard::copy(uint8_t * buffer, uint16_t buffer_length) {
            uint16_t stream_length = this->getLength();
            uint16_t i; // amount of bytes written

            // we use 'getByteStream()' for now this can be replace with a long if/else if condition
            // but this method should be overidden by child classes
            const uint8_t * raw_pointer = this->getByteStream();

            for(i = 0; i < stream_length && i < buffer_length; i++) {
                buffer[i] = raw_pointer[i];
            }

            return i;
        }

        const uint8_t * Standard::getByteStream() const {
            return (uint8_t *) this;
        }
        uint16_t Standard::getLength() const {
            return (uint16_t) (this->length[0] << 8) + this->length[1];
        }
        uint16_t Standard::getExtraDataLength() const {
            return (uint16_t) (this->extra_data_length[0] << 8) + this->extra_data_length[1];
        }
    }
}
