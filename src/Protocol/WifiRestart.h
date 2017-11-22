#ifndef AF820_SMARTLIGHT_PROTOCOL_WIFIRESTART_H_
#define AF820_SMARTLIGHT_PROTOCOL_WIFIRESTART_H_

#include "Wifi.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        class WifiRestart : public Wifi {
        public:
            WifiRestart();
        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_WIFIRESTART_H_
