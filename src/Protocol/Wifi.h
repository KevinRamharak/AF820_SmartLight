#ifndef AF820_SMARTLIGHT_PROTOCOL_WIFI_H_
#define AF820_SMARTLIGHT_PROTOCOL_WIFI_H_

#include "Standard.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        // @NOTE(kevin@ramharak.nl): This class should probably be virtual (/abstract).
        // Reason it is not is the virtual function table. (?) This increases the 'sizeof()' and im not sure if this is only the class itself or also any (child)instances
        // it might conflict with the assumption that the class is an internal memory representation of the protocol
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
