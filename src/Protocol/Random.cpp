#include "Random.h"

namespace AF820_SmartLight {
    namespace Protocol {
        Random::Random() {
            this->setLength((uint8_t) 0x26);
            this->setExtraDataLength((uint8_t) 0x01);
            this->setDeviceFunction(DeviceFunction::RANDOM);
        }

        Random::Random(bool state) {
            this->setLength((uint8_t) 0x26);
            this->setExtraDataLength((uint8_t) 0x01);
            this->setDeviceFunction(DeviceFunction::RANDOM);
            this->setRandomValue(state);
        }

        Random::Random(uint8_t state) {
            this->setLength((uint8_t) 0x26);
            this->setExtraDataLength((uint8_t) 0x01);
            this->setDeviceFunction(DeviceFunction::RANDOM);
            this->setRandomValue(state);
        }

        void Random::setRandomValue(bool state) {
            this->random = state;
        }
        void Random::setRandomValue(uint8_t state) {
            this->random = state > 0;
        }
    }
}
