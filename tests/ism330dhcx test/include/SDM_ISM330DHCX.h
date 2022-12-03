#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_ISM330DHCX.h>

class SDM_ISM330DHCX {
    public:

    SDM_ISM330DHCX();

    // accelerometer: 2g, gyro: 125dps
    bool setup();
    void loop(); // integration routine for gyro goes here

    bool getStatus();

    // g's
    float getAccelX();
    float getAccelY();
    float getAccelZ();
    float getAccelLon();
    float getAccelLat();

    // dps
    float getRollRate();
    float getPitchRate();
    float getYawRate();

    // degrees
    float getRoll(); // x
    float getPitch(); // y
    float getYaw(); // z

    String toDebug();

    void getCAN(uint8_t* payload);

    protected:
    void calibrate(); // determine noise
    void gyroIntegrate();

    SparkFun_ISM330DHCX imu;
    sfe_ism_data_t accelData;
    sfe_ism_data_t gyroData;
};
