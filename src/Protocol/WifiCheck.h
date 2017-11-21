#ifndef AF820_SMARTLIGHT_PROTOCOL_WIFICHECK_H_
#define AF820_SMARTLIGHT_PROTOCOL_WIFICHECK_H_

#include "Wifi.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        class WifiCheck : public Wifi {
        public:
            WifiCheck();
        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_WIFICHECK_H_
