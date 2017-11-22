#include "WifiRestart.h"

namespace AF820_SmartLight {
    namespace Protocol {
        WifiRestart::WifiRestart() {
            this->setWifiFunction(WifiFunction::RESTART);
        }
    }
}
