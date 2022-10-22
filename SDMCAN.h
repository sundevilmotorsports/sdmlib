#include <vector>
#include <FlexCAN_T4.h>

class SDMCAN {
    public: 
    
    // message id 0x360
    enum CANData {
        AccelData,
        RotationData,
        YawProbeData,
        PressueData,
        FLData,
        FRData
    };
    
    void send(CANData type, std::vector<float> data);
    void send(CANData type, std::vector<int> data);
};