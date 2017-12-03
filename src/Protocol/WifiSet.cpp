#include "WifiSet.h"

namespace AF820_SmartLight {
    namespace Protocol {
        void WifiSet::alignBuffer() {
            uint8_t ssid_len = this->ssid.length();
            uint8_t password_len = this->password.length();

            // at offset 0 put ssid_len
            this->buffer[0] = ssid_len;
            // i != 32  => max ssid length is 32
            for(uint8_t i = 0; i < ssid_len; i++) {
                // write the string from the offset 1
                this->buffer[i + 1] = this->ssid[i];
            }

            // at offset ssid_len + 1 put password_len
            // the 1 comes from the byte reserved for ssid_len
            this->buffer[ssid_len + 1] = password_len;

            // i != 64 => max password length is 64
            for(uint8_t i = 0; i < password_len; i++) {
                // write the string from the offset 1
                this->buffer[i + 2 + ssid_len] = this->password[i];
            }

            // update protocol byte lengths       base + wifi_function + data
            uint8_t extraDataLength = (uint8_t) 0x01 + (uint8_t) (ssid_len + password_len + 2);
            uint8_t totalPacketLength = (uint8_t) 0x25 + extraDataLength;
            this->setLength(totalPacketLength);
            this->setExtraDataLength(extraDataLength);
        }

        WifiSet::WifiSet() {
            this->setWifiFunction(WifiFunction::SET);
            this->setSSID("");
            this->setPassword("");
            this->alignBuffer();
        }

        WifiSet::WifiSet(std::string ssid, std::string password) {
            this->setWifiFunction(WifiFunction::SET);
            this->setSSID(ssid);
            this->setPassword(password);
            this->alignBuffer();
        }
        WifiSet::WifiSet(const char * ssid, const char * password) {
            this->setWifiFunction(WifiFunction::SET);
            this->setSSID(ssid);
            this->setPassword(password);
            this->alignBuffer();
        }
        WifiSet::WifiSet(const char * ssid, uint8_t ssid_len, const char * password, uint8_t password_len) {
            this->setWifiFunction(WifiFunction::SET);
            this->setSSID(ssid, ssid_len);
            this->setPassword(password, password_len);
            this->alignBuffer();
        }

        void WifiSet::setSSID(std::string ssid) {
            this->ssid = ssid;
            this->checkSSID();
        }
        void WifiSet::setPassword(std::string password) {
            this->password = password;
            this->checkPassword();
        }

        // (char * str) -> 0 terminated string
        // (char * str, uint8_t len) -> fixed length string
        void WifiSet::setSSID(const char * ssid) {
            this->ssid = std::string(ssid);
            this->checkSSID();
        }
        void WifiSet::setSSID(const char * ssid, uint8_t len) {
            this->ssid = std::string(ssid, len);
            this->checkSSID();
        }

        void WifiSet::setPassword(const char * password) {
            this->password = std::string(password);
            this->checkPassword();
        }
        void WifiSet::setPassword(const char * password, uint8_t len) {
            this->password = std::string(password, len);
            this->checkPassword();
        }

        void WifiSet::checkSSID() {
            if(this->ssid.length() > 32) {
                this->ssid = this->ssid.substr(0, 32);
            }
            this->alignBuffer();
        }

        void WifiSet::checkPassword() {
            if(this->password.length() > 64) {
                this->password = this->password.substr(0, 64);
            }
            this->alignBuffer();
        }
    }
}
