#include "Status.h"

namespace AF820_SmartLight {
    namespace Protocol {
        Status::Status() {
            this->setDeviceFunction(DeviceFunction::STATUS);
        }
    }
}
