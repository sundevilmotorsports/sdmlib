#pragma once

#include "Sensor.h"

class LinearPot : public Sensor {
    public:
    LinearPot(); // TODO
    void initialize(const int pin, float scale);
    int calibrate(int samples = 500);
    void reset();
    float get();
    int getRaw();
    float getDisplacement();
    String toString();

    protected:
    int pin;
    float avg;
    float scale;
    float zeroValue = 0.0;
    float sum=0;
};