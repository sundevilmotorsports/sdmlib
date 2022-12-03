#include "SDMCAN.h"
#include <cmath>

SDMCAN::SDMCAN(){
    
}

SDMCAN::SDMCAN(FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CAN){
    Can0 = CAN;
}

void SDMCAN::send(SDMCAN::CANData type, std::vector<float> data)
{
    switch(type) {
        case SDMCAN::CANData::AccelData:
            CAN_message_t msg;
            msg.id = 0x360;

            // Convert data to unsigned int
            uint xData = round(data[0]);
            uint yData = round(data[1]);
            uint zData = round(data[2]);

            msg.buf[0] = xData >> 8; 
            msg.buf[1] = remainder(xData,256); 
            msg.buf[2] = yData >> 8;
            msg.buf[3] = remainder(yData,256);
            msg.buf[4] = zData >> 8;
            msg.buf[5] = remainder(zData,256);

            Can0.write(msg);
            break;
        case SDMCAN::CANData::RotationData:
            CAN_message_t msg;
            msg.id = 0x361;
            uint pitch = round(data[0]);
            uint roll = round(data[1]);
            uint yaw = round(data[2]);

            msg.buf[0] = pitch >> 8;
            msg.buf[1] = remainder(pitch,256);
            msg.buf[2] = roll >> 8;
            msg.buf[3] = remainder(roll,256);
            msg.buf[4] = yaw >> 8;
            msg.buf[5] = remainder(yaw,256);
            
            Can0.write(msg);
            break;
        case SDMCAN::CANData::YawProbeData:
            CAN_message_t msg;
            msg.id = 0x362;
            uint airSpeed = round(data[0]);
            uint yawAngle = round(data[1]);


            msg.buf[0] = airSpeed >> 8;
            msg.buf[1] = remainder(airSpeed,256);
            msg.buf[2] = yawAngle >> 8;
            msg.buf[3] = remainder(yawAngle,256);
            
            Can0.write(msg);

            break;
        case SDMCAN::CANData:AnglePressureHeightData:
            CAN_message_t msg;
            msg.id = 0x363;
            uint steeringAngle = round(data[0]);
            uint frontBrakePressure = round(data[1]);
            uint rearBrakePressure = round(data[2]);
            uint frontRideHeight = round(data[3])

            msg.buf[0] = steeringAngle >> 8;
            msg.buf[1] = remainder(steeringAngle,256);
            msg.buf[2] = frontBrakePressure >> 8;
            msg.buf[3] = remainder(frontBreakPressure,256);
            msg.buf[4] = rearBreakPressure >> 8;
            msg.buf[5] = remainder(rearBreakPressure,256);
            msg.buf[6] = frontRideHeight >> 8;
            msg.buf[7] = remainder(frontRideHeight,256);
            
            Can0.write(msg);

            break;
        case SDMCAN::CANData::FLData:
            CAN_message_t msg;
            msg.id = 0x364;
            uint damperTravel = round(data[0]);
            uint wheelSpeed = round(data[1]);
            uint brakeRotorTemperature = round(data[2]);
            uint pushRodLoad = round(data[3]);


            msg.buf[0] = damperTravel >> 8;
            msg.buf[1] = remainder(damperTravel,256);
            msg.buf[2] = wheelSpeed >> 8;
            msg.buf[3] = remainder(wheelSpeed,256);
            msg.buf[4] = brakeRotorTemperature >> 8;
            msg.buf[5] = remainder(brakeRotorTemperature,256);
            msg.buf[6] = pushRodLoad >> 8;
            msg.buf[7] = remainder(pushRodLoad,256);
            
            Can0.write(msg);

            break;
        case SDMCAN::CANData::FRData:
            CAN_message_t msg;
            msg.id = 0x365;
            uint damperTravel = round(data[0]);
            uint wheelSpeed = round(data[1]);
            uint brakeRotorTemperature = round(data[2]);
            uint pushRodLoad = round(data[3]);


            msg.buf[0] = damperTravel >> 8;
            msg.buf[1] = remainder(damperTravel,256);
            msg.buf[2] = wheelSpeed >> 8;
            msg.buf[3] = remainder(wheelSpeed,256);
            msg.buf[4] = brakeRotorTemperature >> 8;
            msg.buf[5] = remainder(brakeRotorTemperature,256);
            msg.buf[6] = pushRodLoad >> 8;
            msg.buf[7] = remainder(pushRodLoad,256);

            break;
    }
}

std::vector<float> SDMCAN::recieve(CAN_message_t message)
{
    std::vector<float> messageInfo;
    switch(message.id) {
        case 0x360:
            uint xData = msg.buf[1] + (msg.buf[0] << 8);
            uint yData = msg.buf[3] + (msg.buf[2] << 8);
            uint zData = msg.buf[5] + (msg.buf[4] << 8);

            messageInfo.push_back(xData);
            messageInfo.push_back(yData);
            messageInfo.push_back(zData);
        
            break;

        case 0x361:
            uint pitch = msg.buf[1] + (msg.buf[0] << 8);
            uint roll = msg.buf[3] + (msg.buf[2] << 8);
            uint yaw = msg.buf[5] + (msg.buf[4] << 8);

            messageInfo.push_back(pitch);
            messageInfo.push_back(roll);
            messageInfo.push_back(yaw);

            break;

        case 0x362:
            uint airSpeed = msg.buf[1] + (msg.buf[0] << 8);
            uint yawAngle = msg.buf[3] + (msg.buf[2] << 8);

            messageInfo.push_back(airSpeed);
            messageInfo.push_back(yawAngle);

            break;

        case 0x363:
            uint steeringAngle = msg.buf[1] + (msg.buf[0] << 8);
            uint frontBrakePressure = msg.buf[3] + (msg.buf[2] << 8);
            uint rearBrakePressure = msg.buf[5] + (msg.buf[4] << 8);
            uint frontRideHeight = msg.buf[7] + (msg.buf[6] << 8);
            
            messageInfo.push_back(steeringAngle);
            messageInfo.push_back(frontBrakePressure);
            messageInfo.push_back(rearBrakePressure);
            messageInfo.push_back(frontRideHeight);

            break;

        case 0x364:
            uint damperTravel = msg.buf[1] + (msg.buf[0] << 8);
            uint wheelSpeed = msg.buf[3] + (msg.buf[2] << 8);
            uint brakeRotorTemperature = msg.buf[5] + (msg.buf[4] << 8);
            uint pushRodLoad = msg.buf[7] + (msg.buf[6] << 8);
            
            messageInfo.push_back(damperTravel);
            messageInfo.push_back(wheelSpeed);
            messageInfo.push_back(brakeRotorTemperature);
            messageInfo.push_back(pushRodLoad);

            break;

        case 0x365:
            uint damperTravel = msg.buf[1] + (msg.buf[0] << 8);
            uint wheelSpeed = msg.buf[3] + (msg.buf[2] << 8);
            uint brakeRotorTemperature = msg.buf[5] + (msg.buf[4] << 8);
            uint pushRodLoad = msg.buf[7] + (msg.buf[6] << 8);
            
            messageInfo.push_back(damperTravel);
            messageInfo.push_back(wheelSpeed);
            messageInfo.push_back(brakeRotorTemperature);
            messageInfo.push_back(pushRodLoad);

            break;
        
    }
    return messageInfo;
}