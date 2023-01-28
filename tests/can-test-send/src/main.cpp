#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "SDMCAN.h"
#include <vector>

FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> Can0;
SDMCAN sdmCan = SDMCAN(Can0);

void setup() {
  Serial.begin(9600); delay(400);
  Can0.begin();
  Can0.setBaudRate(1000000);
  Can0.setMaxMB(16);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.mailboxStatus();
  pinMode(13, OUTPUT);
}

void loop() {
  static uint32_t timeout = millis();
  if(millis() - timeout > 200){
    std::vector<float> data{1213, 3233, 1213};
    sdmCan.send(SDMCAN::CANData::AccelerationData, data);
  }
}

