#include <iostream>
#include <cstdio>

#include "Protocol/Color.h"
#include "Protocol/DeviceFunction.h"
#include "Protocol/On.h"
#include "Protocol/Off.h"
#include "Protocol/Random.h"
#include "Protocol/Reset.h"
#include "Protocol/Response.h"
#include "Protocol/Sleep.h"
#include "Protocol/Standard.h"
#include "Protocol/Status.h"
#include "Protocol/Wifi.h"
#include "Protocol/WifiCheck.h"
#include "Protocol/WifiResponse.h"
#include "Protocol/WifiRestart.h"
#include "Protocol/WifiSet.h"

#include "UDP/send.h"

using namespace AF820_SmartLight::Protocol;
using namespace AF820_SmartLight::UDP;

void printPacket(Standard & packet) {
    uint16_t len = packet.getLength();
    uint8_t buffer[len] {};
    packet.copy(buffer, len);

    for(uint16_t i = 0; i < len; i++) {
        if(i % 10 == 0) printf("\n");

        if(i < 10) {
            printf("|  %u : 0x%02x ", i, buffer[i]);
        } else {
            printf("| %u : 0x%02x ", i, buffer[i]);
        }
    }
    printf("\n");

    // print out SSID and password in plain text if wifi packet
    if((DeviceFunction)buffer[20] == DeviceFunction::WIFI && (WifiFunction)buffer[37] == WifiFunction::SET) {
        /*
        38 == buffer[37] == wifi function
        39 == buffer[38] == ssid len
        38 + buffer[38]  == password len
        */
        printf("SSID: ");
        for(uint16_t i = 39; i < len; i++) {
            if(i == 39 + buffer[38]) {
                printf("\nPASS: ");
            }
            if(isprint(buffer[i]))
                printf("%c", buffer[i]);
       }
       printf("\n");
    }
}


int main(int argc, char ** argv) {
    const char * ip = "10.0.0.255";
    const uint16_t port = 5880;
    // destination mac is really weird
    // lamp 1
    // actual mac = 0x62, 0x01, 0x94 ,0x14, 0xB4, 0xC6
    // dest_mac = 0x00, 0x00, 0x00, 0x00, 0xc6, 0xb4, 0x14, 0x00
    const uint8_t dest_mac[] = { 0x00, 0x00, 0xc6, 0xb4, 0x14, 0x00 };

    Color packet;

    packet.setDeviceCode(0x20);
    packet.setDeviceMac(dest_mac);

    // really crude argument checking
    if(argc > 1)
        packet.setRed((uint8_t)std::atoi(argv[1]));
    if(argc > 2)
        packet.setGreen((uint8_t)std::atoi(argv[2]));
    if(argc > 3)
        packet.setBlue((uint8_t)std::atoi(argv[3]));
    if(argc > 4)
        packet.setWhite((uint8_t)std::atoi(argv[4]));

    uint8_t buffer[packet.getLength()];
    packet.copy(buffer, packet.getLength());

    return AF820_SmartLight::UDP::send(ip, port, buffer, packet.getLength()) != true;
}
