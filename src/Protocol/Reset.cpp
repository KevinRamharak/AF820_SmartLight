#include "Reset.h"

namespace AF820_SmartLight {
    namespace Protocol {
        Reset::Reset() {
            this->setDeviceFunction(DeviceFunction::RESET);
        }
    }
}
