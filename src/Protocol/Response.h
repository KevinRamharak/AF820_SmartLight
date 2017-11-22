#ifndef AF820_SMARTLIGHT_PROTOCOL_RESPONSE_H_
#define AF820_SMARTLIGHT_PROTOCOL_RESPONSE_H_

#include "Standard.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        class Response : public Standard {
        protected:
            uint8_t status = 0x00;
            uint8_t random = 0x00;
            uint8_t red[2] { 0x00, 0x00 };
            uint8_t green[2] { 0x00, 0x00 };
            uint8_t blue[2] { 0x00, 0x00 };
            uint8_t white[2] { 0x00, 0x00 };
            uint8_t time[2] { 0x00, 0x00 };
            uint8_t lux[2] { 0x00, 0x00 };
            uint8_t sleep[2] { 0x00, 0x00 };

            // #NOTE: really carefull with this one
            uint8_t * getWriteByteStream();

        public:
            Response();

            /* fill packet with byte stream
                @returns amount of bytes written
            */
            uint16_t fill(uint8_t * src, uint16_t len);

            void setStatus(bool status);
            void setStatus(uint8_t status);

            void setRandom(bool random);
            void setRandom(uint8_t random);

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

            void setLux(uint8_t value);
            void setLux(uint8_t * value);
            void setLux(uint16_t value);

            void setSleep(uint8_t value);
            void setSleep(uint8_t * value);
            void setSleep(uint16_t value);
        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_RESPONSE_H_
