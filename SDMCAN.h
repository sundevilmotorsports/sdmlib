#include <vector>
#include <FlexCAN_T4.h>

class SDMCAN {

    public: 
    enum CANData {
        AccelData, //id = 360
        RotationData, //id  = 361
        YawProbeData, // air speed, yaw angle, id = 362
        AnglePressureHeightData, // front brake pressure, rear brake pressure, id = 363
        FrontLeftData, // Damper Travel, Wheel Speed, Brake Rotor Temperature, Push Rod Load, id = 364
        FrontRightData // Damper Travel, Wheel Speed, Brake Rotor Temperature, Push Rod Load, id = 365
    };
    FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
    
    SDMCAN();   
    SDMCAN(FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CAN);   
    void send(CANData type, std::vector<float> data);
    std::vector<float> recieve(CAN_message_t message);
};