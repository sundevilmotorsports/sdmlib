//Mostly stolen from https://registry.platformio.org/libraries/adafruit/Adafruit%20GPS%20Library

#include <Arduino.h>
#include <Adafruit_GPS.h>
//#include <SoftwareSerial.h>

Adafruit_GPS GPS(&Wire); //Connect to whatever port is being used
#define GPSECHO true

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  GPS.begin(9600);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  delay(1000);  
}

uint32_t timer = millis();

void loop() {
  // put your main code here, to run repeatedly:

  char c = GPS.read();

  if (GPSECHO)
    if (c) Serial.print(c);

  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    Serial.print("\nTime: ");


    if (GPS.hour < 10) { Serial.print('0'); }
    
    Serial.print(GPS.hour, DEC);
    Serial.print(':');
    
    if (GPS.minute < 10) { Serial.print('0'); }
    
    Serial.print(GPS.minute, DEC);
    Serial.print(':');
    
    if (GPS.seconds < 10) { Serial.print('0'); }

    Serial.print(GPS.seconds, DEC);
    Serial.print('.');
    
    if (GPS.milliseconds < 10) {Serial.print("00");}
    else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {Serial.print("0");}


    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }
}