#include <Arduino.h>
#include <vector>

// pin on the teensy
const int pin = A6;

// multiplier
float scale = 0.00244379;

// gets the value of the potentiometer in inches 
float get(){
    return scale * abs(analogRead(pin));
}

// gets the raw analog value of the potentiometer
int getRaw(){
    return analogRead(pin);
}

////////////////////////////////

// zero'd location of the potentiometer
float zeroValue = 0.0;
float sum=0;

// zero's out the potentiometer
// i.e., set the zero'd location
void calibrate(int samples){
    
    using std::vector;
    static vector<float> values(samples);
    for (int i = 0; i < samples; i++){
        values.insert(values.begin(), get());
        sum = sum+get();
    }
    zeroValue = sum/samples;
}


// returns the displacement of the potentiometer from its zero'd position
float getDisplacement(){
    float displacement = get();
    displacement = zeroValue - displacement;
    return displacement;
}


void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    calibrate(500);
}

void loop() {
    // put your main code here, to run repeatedly:
    getDisplacement();
    Serial.println(getDisplacement());
}