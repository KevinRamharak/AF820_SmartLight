#include "Response.h"

namespace AF820_SmartLight {
    namespace Protocol {
        Response::Response() {
            this->setLength((uint8_t) 0x35);
            this->setExtraDataLength((uint8_t) 0x10);
            this->setDeviceFunction(DeviceFunction::RESPONSE);
        }

        uint8_t * Response::getWriteByteStream() {
            return (uint8_t *) this;
        }

        uint16_t Response::fill(uint8_t * src, uint16_t len) {
            uint8_t * pointer = this->getWriteByteStream();
            uint16_t length = this->getLength();
            uint16_t i;

            for(i = 0; i < len && i < length; i++) {
                pointer[i] = src[i];
            }

            return i;
        }

        void Response::setStatus(bool status) {
            this->status = status;
        }
        void Response::setStatus(uint8_t status) {
            this->status = status > 0;
        }

        void Response::setRandom(bool random) {
            this->random = random;
        }
        void Response::setRandom(uint8_t random) {
            this->random = random > 0;
        }

        void Response::setRed(uint8_t value) {
            this->red[0] = 0x00;
            this->red[1] = value;
        }
        void Response::setRed(uint8_t * value) {
            this->red[0] = value[0];
            this->red[1] = value[1];
        }
        void Response::setRed(uint16_t value) {
            this->red[0] = (uint8_t) (value >> 8);
            this->red[1] = (uint8_t) value;
        }

        void Response::setGreen(uint8_t value) {
            this->green[0] = 0x00;
            this->green[1] = value;
        }
        void Response::setGreen(uint8_t * value) {
            this->green[0] = value[0];
            this->green[1] = value[1];
        }
        void Response::setGreen(uint16_t value) {
            this->green[0] = (uint8_t) (value >> 8);
            this->green[1] = (uint8_t) value;
        }

        void Response::setBlue(uint8_t value) {
            this->blue[0] = 0x00;
            this->blue[1] = value;
        }
        void Response::setBlue(uint8_t * value) {
            this->blue[0] = value[0];
            this->blue[1] = value[1];
        }
        void Response::setBlue(uint16_t value) {
            this->blue[0] = (uint8_t) (value >> 8);
            this->blue[1] = (uint8_t) value;
        }

        void Response::setWhite(uint8_t value) {
            this->white[0] = 0x00;
            this->white[1] = value;
        }
        void Response::setWhite(uint8_t * value) {
            this->white[0] = value[0];
            this->white[1] = value[1];
        }
        void Response::setWhite(uint16_t value) {
            this->white[0] = (uint8_t) (value >> 8);
            this->white[1] = (uint8_t) value;
        }

        void Response::setTime(uint8_t value) {
            this->time[0] = 0x00;
            this->time[1] = value;
        }
        void Response::setTime(uint8_t * value) {
            this->time[0] = value[0];
            this->time[1] = value[1];
        }
        void Response::setTime(uint16_t value) {
            this->time[0] = (uint8_t) (value >> 8);
            this->time[1] = (uint8_t) value;
        }

        void Response::setLux(uint8_t value) {
            this->lux[0] = 0x00;
            this->lux[1] = value;
        }
        void Response::setLux(uint8_t * value) {
            this->lux[0] = value[0];
            this->lux[1] = value[1];
        }
        void Response::setLux(uint16_t value) {
            this->lux[0] = (uint8_t) (value >> 8);
            this->lux[1] = (uint8_t) value;
        }

        void Response::setSleep(uint8_t value) {
            this->sleep[0] = 0x00;
            this->sleep[1] = value;
        }
        void Response::setSleep(uint8_t * value) {
            this->sleep[0] = value[0];
            this->sleep[1] = value[1];
        }
        void Response::setSleep(uint16_t value) {
            this->sleep[0] = (uint8_t) (value >> 8);
            this->sleep[1] = (uint8_t) value;
        }
    }
}
