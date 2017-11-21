#include "Wifi.h"

namespace AF820_SmartLight {
    namespace Protocol {
        Wifi::Wifi() {
            this->setLength((uint8_t) 0x26);
            this->setExtraDataLength((uint8_t) 0x01);
            this->setDeviceFunction(DeviceFunction::WIFI);
        }

        void Wifi::setWifiFunction(const uint8_t func) {
            this->wifi_function = func;
        }
        void Wifi::setWifiFunction(const WifiFunction func) {
            this->wifi_function = (uint8_t) func;
        }
    }
}
