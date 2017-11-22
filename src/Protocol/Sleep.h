#ifndef AF820_SMARTLIGHT_PROTOCOL_SLEEP_H_
#define AF820_SMARTLIGHT_PROTOCOL_SLEEP_H_

#include "Standard.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        class Sleep : public Standard {
        protected:
            uint8_t sleep[2] { 0x00, 0x00 };
        public:
            Sleep();
            Sleep(uint8_t value);
            Sleep(uint8_t * value);
            Sleep(uint16_t value);

            void setSleepValue(uint8_t value);
            void setSleepValue(uint8_t * value);
            void setSleepValue(uint16_t value);
        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_SLEEP_H_
