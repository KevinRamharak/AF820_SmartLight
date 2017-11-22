#include "WifiResponse.h"

namespace AF820_SmartLight {
    namespace Protocol {
        WifiResponse::WifiResponse() {
            this->setWifiFunction(WifiFunction::RESPONSE);
        }
    }
}
