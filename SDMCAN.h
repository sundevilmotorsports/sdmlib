#include <vector>
#include <FlexCAN_T4.h>

class SDMCAN {
    
    
    public: 
    // message id 0x360
    enum CANData {
        AccelData,
        RotationData,
        // air speed, yaw angle
        YawProbeData,
        // front brake pressure, rear brake pressure
        AnglePressureHeightData,
        // Damper Travel, Wheel Speed, Brake Rotor Temperature, Push Rod Load
        // for both
        FrontLeftData,
        FrontRigtData
    };
    FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
    
    SDMCAN();   
    SDMCAN(FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CAN);   
    void send(CANData type, std::vector<float> data);
    std::vector<float> recieve(CAN_message_t message);
};