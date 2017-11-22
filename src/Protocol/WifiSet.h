#ifndef AF820_SMARTLIGHT_PROTOCOL_WIFISET_H_
#define AF820_SMARTLIGHT_PROTOCOL_WIFISET_H_

#include <string>

#include "Wifi.h"
#include "DeviceFunction.h"

namespace AF820_SmartLight {
    namespace Protocol {
        class WifiSet : public Wifi {
        protected:
            uint8_t buffer[32 + 64 + 2] {}; // 1 : SSID_LEN + 32 : SSID + 1 : password_LEN 64 : password
            std::string ssid;
            std::string password;

            void alignBuffer();

        public:
            WifiSet();
            WifiSet(std::string ssid, std::string password);
            WifiSet(const char * ssid, const char * password);
            WifiSet(const char * ssid, uint8_t ssid_len, const char * password, uint8_t password_len);

            void setSSID(std::string ssid);
            void setPassword(std::string password);

            // (char * str) -> 0 terminated string
            // (char * str, uint8_t len) -> fixed length string
            void setSSID(const char * ssid);
            void setSSID(const char * ssid, uint8_t len);
            void setPassword(const char * password);
            void setPassword(const char * password, uint8_t len);

            // trunctuate value to max length
            void checkSSID();
            void checkPassword();
        };
    }
}

#endif// AF820_SMARTLIGHT_PROTOCOL_WIFISET_H_
