#include "SDMCAN.h"

#include <cmath>
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

void SDMCAN::send(SDMCAN::CANData type, std::vector<float> data){
    switch(type) {
        case SDMCAN::CANData::AccelData:
            CAN_message_t msg;
            msg.id = 0x360;
            uint XData = round((data[0]*100);
            uint YData = round((data[1]*100);
            uint ZData = round((data[2]*100);

            msg.buf[0] = XData << 8;
            msg.buf[1] = remainder(XData,256);
            msg.buf[2] = YData << 8;
            msg.buf[3] = remainder(YData,256);
            msg.buf[4] = ZData << 8;
            msg.buf[5] = remainder(ZData,256);

            Can0.write(msg);
            break;
        case SDMCAN::CANData::RotationData:
            CAN_message_t msg;
            msg.id = 0x361;
            uint Pitch = round((data[0]*100);
            uint Roll = round((data[1]*100);
            uint Yaw = round((data[2]*100);

            msg.buf[0] = Pitch << 8;
            msg.buf[1] = remainder(Pitch,256);
            msg.buf[2] = Roll << 8;
            msg.buf[3] = remainder(Roll,256);
            msg.buf[4] = Yaw << 8;
            msg.buf[5] = remainder(Yaw,256);
            
            Can0.write(msg);
            break;
        case SDMCAN::CANData::YawProbeData:
            
            break;
        case SDMCAN::CANData::PressueData:
            
            break;
        case SDMCAN::CANData::FLData:
            
            break;
        case SDMCAN::CANData::FRData:
            
            break;
    }
}