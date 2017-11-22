#ifndef AF820_SMARTLIGHT_PROTOCOL_COLOR_H_
#define AF820_SMARTLIGHT_PROTOCOL_COLOR_H_

#include "Standard.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        class Color : public Standard {
        protected:
            uint8_t red[2] { 0x00, 0x00 };
            uint8_t green[2] { 0x00, 0x00 };
            uint8_t blue[2] { 0x00, 0x00 };
            uint8_t white[2] { 0x00, 0x00 };
            uint8_t time[2] { 0x00, 0x00 };
            uint8_t lum[2] { 0x00, 0x00 };

        public:
            Color();
            Color(uint8_t red, uint8_t green, uint8_t blue);
            Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
            Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white, uint8_t time);
            Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white, uint8_t time, uint8_t lum);

            Color(uint8_t * red, uint8_t * green, uint8_t * blue);
            Color(uint8_t * red, uint8_t * green, uint8_t * blue, uint8_t * white);
            Color(uint8_t * red, uint8_t * green, uint8_t * blue, uint8_t * white, uint8_t * time);
            Color(uint8_t * red, uint8_t * green, uint8_t * blue, uint8_t * white, uint8_t * time, uint8_t * lum);

            Color(uint16_t red, uint16_t green, uint16_t blue);
            Color(uint16_t red, uint16_t green, uint16_t blue, uint16_t white);
            Color(uint16_t red, uint16_t green, uint16_t blue, uint16_t white, uint16_t time);
            Color(uint16_t red, uint16_t green, uint16_t blue, uint16_t white, uint16_t time, uint16_t lum);

            void setRed(uint8_t value);
            void setRed(uint8_t * value);
            void setRed(uint16_t value);

            void setGreen(uint8_t value);
            void setGreen(uint8_t * value);
            void setGreen(uint16_t value);

            void setBlue(uint8_t value);
            void setBlue(uint8_t * value);
            void setBlue(uint16_t value);

            void setWhite(uint8_t value);
            void setWhite(uint8_t * value);
            void setWhite(uint16_t value);

            void setTime(uint8_t value);
            void setTime(uint8_t * value);
            void setTime(uint16_t value);

            void setLumenosity(uint8_t value);
            void setLumenosity(uint8_t * value);
            void setLumenosity(uint16_t value);
        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_COLOR_H_
