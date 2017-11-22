#include "WifiSet.h"

namespace AF820_SmartLight {
    namespace Protocol {
        void WifiSet::alignBuffer() {
            uint8_t ssid_len = this->ssid->lenght();
            uint8_t password_len = this->password->length();

            // at offset 0 put ssid_len
            this->buffer[0] = ssid_len;
            // i < ssid_len - 1     => ignore the terminating null char
            // i != 32  => max ssid length is 32
            for(uint8_t i = 0; i < ssid_len - 1 && i != 32; i++) {
                // write the string from the offset 1
                this->buffer[i + 1] = this->ssid[i];
            }

            // at offset ssid_len + 1 put password_len
            // the 1 comes from the byte reserved for ssid_len
            this->buffer[ssid_len + 1] = password_len;

            // i < password_len - 1 => ignore the terminating null char
            // i != 64 => max password length is 64
            for(uint8_t i = 0; i < password_len - 1 && i != 64; i++) {
                // write the string from the offset 1
                this->buffer[i + 1] = this->password[i];
            }

            // update protocol byte lengths       base + wifi_function + data
            uint8_t extraDataLength = (uint8_t) 0x01 + (uint8_t) (ssid_len + password_len + 2);
            uint8_t totalPacketLength = (uint8_t) 0x25 + extraDataLength;
            this->setLength(totalPacketLength);
            this->setExtraDataLength(extraDataLength);
        }

        WifiSet::WifiSet() {
            this->setWifiFunction(WifiFunction::WIFI_SET);
            this->setSSID("");
            this->setPassword("");
            this->alignBuffer();
        }

        WifiSet::WifiSet(std::string ssid, std::string password) {
            this->setWifiFunction(WifiFunction::WIFI_SET);
            this->setSSID(ssid);
            this->setPassword(password);
            this->alignBuffer();
        }
        WifiSet::WifiSet(char * ssid, char * password) {
            this->setWifiFunction(WifiFunction::WIFI_SET);
            this->setSSID(ssid);
            this->setPassword(password);
            this->alignBuffer();
        }
        WifiSet::WifiSet(char * ssid, uint8_t ssid_len, char * password, uint8_t password_len) {
            this->setWifiFunction(WifiFunction::WIFI_SET);
            this->setSSID(ssid, ssid_len);
            this->setPassword(password, password_len);
            this->alignBuffer();
        }

        void WifiSet::setSSID(std::string ssid) {
            this->ssid = ssid;
        }
        void WifiSet::setPassword(std::string password) {
            this->password = password;
        }

        // (char * str) -> 0 terminated string
        // (char * str, uint8_t len) -> fixed length string
        void WifiSet::setSSID(char * ssid) {
            this->ssid = std::string(ssid);
        }
        void WifiSet::setSSID(char * ssid, uint8_t len) {
            this->ssid = std::string(ssid, len);
        }

        void WifiSet::setPassword(char * password) {
            this->password = std::string(password);
        }
        void WifiSet::setPassword(char * password, uint8_t len) {
            this->password = std::string(password, password_len);
        }
    }
}
