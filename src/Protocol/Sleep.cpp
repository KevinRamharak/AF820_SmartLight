#include "Sleep.h"

namespace AF820_SmartLight {
    namespace Protocol {
        Sleep::Sleep() {
            this->setLength((uint8_t) 0x27);
            this->setExtraDataLength((uint8_t) 0x02);
            this->setDeviceFunction(DeviceFunction::SLEEP);
        }

        Sleep::Sleep(uint8_t value) {
            this->setLength((uint8_t) 0x27);
            this->setExtraDataLength((uint8_t) 0x02);
            this->setDeviceFunction(DeviceFunction::SLEEP);
            this->setSleepValue(value);
        }

        Sleep::Sleep(uint8_t * value) {
            this->setLength((uint8_t) 0x27);
            this->setExtraDataLength((uint8_t) 0x02);
            this->setDeviceFunction(DeviceFunction::SLEEP);
            this->setSleepValue(value);
        }

        Sleep::Sleep(uint16_t value) {
            this->setLength((uint8_t) 0x27);
            this->setExtraDataLength((uint8_t) 0x02);
            this->setDeviceFunction(DeviceFunction::SLEEP);
            this->setSleepValue(value);
        }

        void Sleep::setSleepValue(uint8_t value) {
            this->sleep[0] = 0x00;
            this->sleep[1] = value;
        }
        void Sleep::setSleepValue(uint8_t * value) {
            this->sleep[0] = value[0];
            this->sleep[1] = value[1];
        }
        void Sleep::setSleepValue(uint16_t value) {
            this->sleep[0] = (uint8_t) (value >> 8);
            this->sleep[1] = (uint8_t) value;
        }
    }
}
