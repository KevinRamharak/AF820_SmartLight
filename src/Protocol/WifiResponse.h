#ifndef AF820_SMARTLIGHT_PROTOCOL_WIFIRESPONSE_H_
#define AF820_SMARTLIGHT_PROTOCOL_WIFIRESPONSE_H_

#include "Wifi.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        class WifiResponse : public Wifi {
        public:
            WifiResponse();
        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_WIFIRESPONSE_H_
