#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "SDMCAN.h"
#include <vector>

FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> Can0;
SDMCAN sdmCan;

void canSniff(const CAN_message_t&);


void setup() {
 Serial.begin(9600); delay(400);
  Can0.begin();
  Can0.setBaudRate(1000000);
  Can0.setMaxMB(16);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(canSniff);
  Can0.mailboxStatus();

  sdmCan = SDMCAN(Can0);
}

void loop() {
  Can0.events();
}

void canSniff(const CAN_message_t &msg){
  Serial.print("sniff function");
  std::vector<float> data = sdmCan.recieve(msg);
  for(float i: data){
    Serial.print(i); Serial.print(" ");
  }
}