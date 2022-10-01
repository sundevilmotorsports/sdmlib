#include "LinearPot.h"

LinearPot::LinearPot(){

}

int LinearPot::calibrate(int samples){

    for (int i = 0; i < samples; i++){
        sum = sum+get();
    }
    zeroValue = sum/samples;
    return 0;
}

void LinearPot::initialize(const int pin, float scale){
    this->pin = pin;
    this->scale = scale;
}

float LinearPot::get(){
    return scale * abs(analogRead(pin));
}

int LinearPot::getRaw(){
    return analogRead(pin);
}

float LinearPot::getDisplacement(){
    float displacement = get();
    displacement = zeroValue - displacement;
    return displacement;
}

void LinearPot::reset(){

}



String LinearPot::toString(){
    return "temp";
}