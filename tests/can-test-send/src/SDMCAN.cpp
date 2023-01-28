#include "SDMCAN.h"
#include <vector>
#include <FlexCAN_T4.h>

SDMCAN::SDMCAN(){
    
}

SDMCAN::SDMCAN(FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> CAN){
    this->Can0 = CAN;
}

void SDMCAN::send(SDMCAN::CANData type, std::vector<float> data)
{
    CAN_message_t message;
    switch(type) {
        case SDMCAN::CANData::AccelerationData:
        {
            message.id = 0x360;

            // Convert data to unsigned int
            unsigned int xData = round(data[0]);
            unsigned int yData = round(data[1]);
            unsigned int zData = round(data[2]);

            message.buf[0] = xData >> 8; 
            message.buf[1] = remainder(xData,256); 
            message.buf[2] = yData >> 8;
            message.buf[3] = remainder(yData,256);
            message.buf[4] = zData >> 8;
            message.buf[5] = remainder(zData,256);

            Can0.write(message);
        } break;
        case SDMCAN::CANData::RotationData:
        {
            message.id = 0x361;
            unsigned int pitch = round(data[0]);
            unsigned int roll = round(data[1]);
            unsigned int yaw = round(data[2]);

            message.buf[0] = pitch >> 8;
            message.buf[1] = remainder(pitch,256);
            message.buf[2] = roll >> 8;
            message.buf[3] = remainder(roll,256);
            message.buf[4] = yaw >> 8;
            message.buf[5] = remainder(yaw,256);
            
            Can0.write(message);
        } break;
        case SDMCAN::CANData::YawProbeData:
        {
            message.id = 0x362;
            unsigned int airSpeed = round(data[0]);
            unsigned int yawAngle = round(data[1]);


            message.buf[0] = airSpeed >> 8;
            message.buf[1] = remainder(airSpeed,256);
            message.buf[2] = yawAngle >> 8;
            message.buf[3] = remainder(yawAngle,256);
            
            Can0.write(message);
        } break;
        case SDMCAN::CANData::AnglePressureHeightData:
        {
            message.id = 0x363;

            unsigned int steeringAngle = round(data[0]);
            unsigned int frontBrakePressure = round(data[1]);
            unsigned int rearBrakePressure = round(data[2]);
            unsigned int frontRideHeight = round(data[3]);

            message.buf[0] = steeringAngle >> 8;
            message.buf[1] = remainder(steeringAngle,256);
            message.buf[2] = frontBrakePressure >> 8;
            message.buf[3] = remainder(frontBrakePressure,256);
            message.buf[4] = rearBrakePressure >> 8;
            message.buf[5] = remainder(rearBrakePressure,256);
            message.buf[6] = frontRideHeight >> 8;
            message.buf[7] = remainder(frontRideHeight,256);
            
            Can0.write(message);
        } break;
        case SDMCAN::CANData::FrontLeftData:
        {
            message.id = 0x364;

            unsigned int damperTravel = round(data[0]);
            unsigned int wheelSpeed = round(data[1]);
            unsigned int brakeRotorTemperature = round(data[2]);
            unsigned int pushRodLoad = round(data[3]);


            message.buf[0] = damperTravel >> 8;
            message.buf[1] = remainder(damperTravel,256);
            message.buf[2] = wheelSpeed >> 8;
            message.buf[3] = remainder(wheelSpeed,256);
            message.buf[4] = brakeRotorTemperature >> 8;
            message.buf[5] = remainder(brakeRotorTemperature,256);
            message.buf[6] = pushRodLoad >> 8;
            message.buf[7] = remainder(pushRodLoad,256);
            
            Can0.write(message);
        } break;
        case SDMCAN::CANData::FrontRightData:
        {
            message.id = 0x365;
            
            unsigned int damperTravel = round(data[0]);
            unsigned int wheelSpeed = round(data[1]);
            unsigned int brakeRotorTemperature = round(data[2]);
            unsigned int pushRodLoad = round(data[3]);


            message.buf[0] = damperTravel >> 8;
            message.buf[1] = remainder(damperTravel,256);
            message.buf[2] = wheelSpeed >> 8;
            message.buf[3] = remainder(wheelSpeed,256);
            message.buf[4] = brakeRotorTemperature >> 8;
            message.buf[5] = remainder(brakeRotorTemperature,256);
            message.buf[6] = pushRodLoad >> 8;
            message.buf[7] = remainder(pushRodLoad,256);
        } break;
    }
}

std::vector<float> SDMCAN::recieve(CAN_message_t message)
{
    std::vector<float> messageInfo;
    switch(message.id){
        case 0x360:
        {
            unsigned int xData = message.buf[1] + (message.buf[0] << 8);
            unsigned int yData = message.buf[3] + (message.buf[2] << 8);
            unsigned int zData = message.buf[5] + (message.buf[4] << 8);

            messageInfo.push_back(xData);
            messageInfo.push_back(yData);
            messageInfo.push_back(zData);
        
        } break;
        case 0x361:
        {
            unsigned int pitch = message.buf[1] + (message.buf[0] << 8);
            unsigned int roll = message.buf[3] + (message.buf[2] << 8);
            unsigned int yaw = message.buf[5] + (message.buf[4] << 8);

            messageInfo.push_back(pitch);
            messageInfo.push_back(roll);
            messageInfo.push_back(yaw);

        } break;
        case 0x362:
        {
            unsigned int airSpeed = message.buf[1] + (message.buf[0] << 8);
            unsigned int yawAngle = message.buf[3] + (message.buf[2] << 8);

            messageInfo.push_back(airSpeed);
            messageInfo.push_back(yawAngle);

        } break;
        case 0x363:
        {
            unsigned int steeringAngle = message.buf[1] + (message.buf[0] << 8);
            unsigned int frontBrakePressure = message.buf[3] + (message.buf[2] << 8);
            unsigned int rearBrakePressure = message.buf[5] + (message.buf[4] << 8);
            unsigned int frontRideHeight = message.buf[7] + (message.buf[6] << 8);
            
            messageInfo.push_back(steeringAngle);
            messageInfo.push_back(frontBrakePressure);
            messageInfo.push_back(rearBrakePressure);
            messageInfo.push_back(frontRideHeight);

        } break;
        case 0x364:
        {
            unsigned int damperTravel = message.buf[1] + (message.buf[0] << 8);
            unsigned int wheelSpeed = message.buf[3] + (message.buf[2] << 8);
            unsigned int brakeRotorTemperature = message.buf[5] + (message.buf[4] << 8);
            unsigned int pushRodLoad = message.buf[7] + (message.buf[6] << 8);
            
            messageInfo.push_back(damperTravel);
            messageInfo.push_back(wheelSpeed);
            messageInfo.push_back(brakeRotorTemperature);
            messageInfo.push_back(pushRodLoad);

        } break;
        case 0x365:
        {
            unsigned int damperTravel = message.buf[1] + (message.buf[0] << 8);
            unsigned int wheelSpeed = message.buf[3] + (message.buf[2] << 8);
            unsigned int brakeRotorTemperature = message.buf[5] + (message.buf[4] << 8);
            unsigned int pushRodLoad = message.buf[7] + (message.buf[6] << 8);
            
            messageInfo.push_back(damperTravel);
            messageInfo.push_back(wheelSpeed);
            messageInfo.push_back(brakeRotorTemperature);
            messageInfo.push_back(pushRodLoad);

        } break;
        
    }
    return messageInfo;
}