#include "Color.h"

namespace AF820_SmartLight {
    namespace Protocol {
        // @TODO(kevin@ramharak.nl): maybe refactor all constructors (in all packets) to share common constructor logic in a private/protected 'init()' method
        // @NOTE: uint16_t does not really make sense here because a color is always 1 byte, so 0xFF 0xFF will be trunctuated to 0x00 0xFF
        // #NOTE: 0xFF 0x00 will be trunctuated to 0x00 0xFF
        Color::Color() {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
        }

        // uint8_t
        Color::Color(uint8_t red, uint8_t green, uint8_t blue) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
        }
        Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
            this->setWhite(white);
        }
        Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white, uint8_t time) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
            this->setWhite(white);
            this->setTime(time);
        }
        Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white, uint8_t time, uint8_t lum) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
            this->setWhite(white);
            this->setTime(time);
            this->setLumenosity(lum);
        }

        // uint8_t *
        Color::Color(uint8_t * red, uint8_t * * green, uint8_t * blue) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
        }
        Color::Color(uint8_t * red, uint8_t * green, uint8_t * blue, uint8_t * white) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
            this->setWhite(white);
        }
        Color::Color(uint8_t * red, uint8_t * green, uint8_t * blue, uint8_t * white, uint8_t * time) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
            this->setWhite(white);
            this->setTime(time);
        }
        Color::Color(uint8_t * red, uint8_t * green, uint8_t * blue, uint8_t * white, uint8_t * time, uint8_t * lum) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
            this->setWhite(white);
            this->setTime(time);
            this->setLumenosity(lum);
        }

        // uint16_t
        Color::Color(uint16_t red, uint16_t green, uint16_t blue) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
        }
        Color::Color(uint16_t red, uint16_t green, uint16_t blue, uint16_t white) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
            this->setWhite(white);
        }
        Color::Color(uint16_t red, uint16_t green, uint16_t blue, uint16_t white, uint16_t time) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
            this->setWhite(white);
            this->setTime(time);
        }
        Color::Color(uint16_t red, uint16_t green, uint16_t blue, uint16_t white, uint16_t time, uint16_t lum) {
            this->setLength((uint8_t) 0x31);
            this->setExtraDataLength((uint8_t) 0x0C);
            this->setDeviceFunction(DeviceFunction::COLOR);
            this->setRed(red);
            this->setGreen(green);
            this->setBlue(blue);
            this->setWhite(white);
            this->setTime(time);
            this->setLumenosity(lum);
        }

        void Color::setRed(uint8_t value) {
            this->red[0] = 0x00;
            this->red[1] = value;
        }
        void Color::setRed(uint8_t * value) {
            this->red[0] = value[0];
            this->red[1] = value[1];
        }
        void Color::setRed(uint16_t value) {
            this->red[0] = (uint8_t) (value >> 8);
            this->red[1] = (uint8_t) value;
        }

        void Color::setGreen(uint8_t value) {
            this->green[0] = 0x00;
            this->green[1] = value;
        }
        void Color::setGreen(uint8_t * value) {
            this->green[0] = value[0];
            this->green[1] = value[1];
        }
        void Color::setGreen(uint16_t value) {
            this->green[0] = (uint8_t) (value >> 8);
            this->green[1] = (uint8_t) value;
        }

        void Color::setBlue(uint8_t value) {
            this->blue[0] = 0x00;
            this->blue[1] = value;
        }
        void Color::setBlue(uint8_t * value) {
            this->blue[0] = value[0];
            this->blue[1] = value[1]
        }
        void Color::setBlue(uint16_t value) {
            this->blue[0] = (uint8_t) (value >> 8);
            this->blue[1] = (uint8_t) value;
        }

        void Color::setWhite(uint8_t value) {
            this->white[0] = 0x00;
            this->white[1] = value;
        }
        void Color::setWhite(uint8_t * value) {
            this->white[0] = value[0];
            this->white[1] = value[1]
        }
        void Color::setWhite(uint16_t value) {
            this->white[0] = (uint8_t) (value >> 8);
            this->white[1] = (uint8_t) value;
        }

        void Color::setTime(uint8_t value) {
            this->time[0] = 0x00;
            this->time[1] = value;
        }
        void Color::setTime(uint8_t * value) {
            this->time[0] = value[0];
            this->time[1] = value[1]
        }
        void Color::setTime(uint16_t value) {
            this->time[0] = (uint8_t) (value >> 8);
            this->time[1] = (uint8_t) value;
        }

        void Color::setLumenosity(uint8_t value) {
            this->lum[0] = 0x00;
            this->lum[1] = value;
        }
        void Color::setLumenosity(uint8_t * value) {
            this->lum[0] = value[0];
            this->lum[1] = value[1]
        }
        void Color::setLumenosity(uint16_t value) {
            this->lum[0] = (uint8_t) (value >> 8);
            this->lum[1] = (uint8_t) value;
        }
    }
}

