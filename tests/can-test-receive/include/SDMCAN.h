#include <vector>
#include <FlexCAN_T4.h>

class SDMCAN {

    public: 
    enum CANData {
        AccelerationData, //id = 360
        RotationData, //id  = 361
        YawProbeData, // air speed, yaw angle, id = 362
        AnglePressureHeightData, // front brake pressure, rear brake pressure, id = 363
        // Damper Travel, Wheel Speed, Brake Rotor Temperature, Push Rod Load
        // for both
        FrontLeftData, // id = 364
        FrontRightData // id = 365
    };
    FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> Can0;
    
    SDMCAN();   
    SDMCAN(FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> CAN);   
    void send(CANData type, std::vector<float> data);
    std::vector<float> recieve(CAN_message_t message);
};