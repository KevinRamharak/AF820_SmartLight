#ifndef AF820_SMARTLIGHT_PROTOCOL_WIFI_H_
#define AF820_SMARTLIGHT_PROTOCOL_WIFI_H_

#include "Standard.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        class Wifi : public Standard {
        protected:
            uint8_t wifi_function = 0x00; // this could be of type 'enum struct WifiFunction'
        public:
            Wifi();

            void setWifiFunction(const uint8_t func);
            void setWifiFunction(const WifiFunction func);
        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_WIFI_H_
