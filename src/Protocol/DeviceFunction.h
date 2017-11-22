#ifndef AF820_SMARTLIGHT_PROTOCOL_DEVICEFUNCTION_H_
#define AF820_SMARTLIGHT_PROTOCOL_DEVICEFUNCTION_H_

#include <cstdint>

namespace AF820_SmartLight {
    namespace Protocol {
        enum struct DeviceFunction : uint8_t {
            ON = 0x01,
            OFF = 0x02,
            COLOR = 0x03,
            RANDOM = 0x04,
            SLEEP = 0x05,
            WIFI = 0xF0,
            REGISTER_RESPONSE = 0xFA,
            REGISTER_REQUEST = 0xFB, // weird remote service that the AF820_SmartLight will inform of everything you send it
            RESET = 0xF7,
            RESPONSE = 0xFE,
            STATUS = 0xFF,
        };

        enum struct WifiFunction : uint8_t {
            CHECK = 0x01,
            SET = 0x03,
            RESPONSE = 0x04,
            RESTART = 0x05
        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_DEVICEFUNCTION_H_
