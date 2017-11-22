#ifndef AF820_SMARTLIGHT_PROTOCOL_RANDOM_H_
#define AF820_SMARTLIGHT_PROTOCOL_RANDOM_H_

#include "Standard.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        class Random : public Standard {
        protected:
            uint8_t random = 0x00;
        public:
            Random();
            Random(bool state);
            Random(uint8_t state);

            void setRandomValue(bool state);
            void setRandomValue(uint8_t state);
        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_RANDOM_H_
