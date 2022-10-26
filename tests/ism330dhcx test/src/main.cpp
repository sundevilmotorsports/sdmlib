#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_ISM330DHCX.h"
#include "Logger.h"

SparkFun_ISM330DHCX myISM; 

// Structs for X,Y,Z data
sfe_ism_data_t accelData; 
sfe_ism_data_t gyroData; 

Logger logger;

void setup(){

	Wire.begin();

	Serial.begin(115200);

	if( !myISM.begin() ){
		Serial.println("Did not begin.");
		while(1);
	}

	// Reset the device to default settings. This if helpful is you're doing multiple
	// uploads testing different settings. 
	myISM.deviceReset();

	// Wait for it to finish reseting
	while( !myISM.getDeviceReset() ){ 
		delay(1);
	} 

	Serial.println("Reset.");
	Serial.println("Applying settings.");
	delay(100);
	
	myISM.setDeviceConfig();
	myISM.setBlockDataUpdate();
	
	// Set the output data rate and precision of the accelerometer
	myISM.setAccelDataRate(ISM_XL_ODR_52Hz);
	myISM.setAccelFullScale(ISM_2g); 

	// Set the output data rate and precision of the gyroscope
	myISM.setGyroDataRate(ISM_GY_ODR_52Hz);
	myISM.setGyroFullScale(ISM_125dps); 

	// Turn on the accelerometer's filter and apply settings. 
	myISM.setAccelFilterLP2();
	myISM.setAccelSlopeFilter(ISM_LP_ODR_DIV_100);

	// Turn on the gyroscope's filter and apply settings. 
	myISM.setGyroFilterLP1();
	myISM.setGyroLP1Bandwidth(ISM_MEDIUM);

	// logger setup
	logger.setup();
	logger.initializeFile(
		"jerkPosY",
		{
			"X Acceleration (mG's)", "Y Acceleration (mG's)", "Z Acceleration (mG's)",
			"Pitch rate (mdps)", "Roll rate (mdps)", "Yaw rate (mdps)"
		}
	);
}

void loop(){

	// Check if both gyroscope and accelerometer data is available.
	if( myISM.checkStatus() ){
		myISM.getAccel(&accelData);
		myISM.getGyro(&gyroData);

		// accelerometer data is in mG's
		// gyroscope data is in dps
    ///*
		Serial.print("Accelerometer: ");
		Serial.print("X: ");
		Serial.print(accelData.xData);
		logger.addData("jerkPosY", "X Acceleration (mG's)", accelData.xData);
		Serial.print(" ");
		Serial.print("Y: ");
		Serial.print(accelData.yData);
		logger.addData("jerkPosY", "Y Acceleration (mG's)", accelData.yData);
		Serial.print(" ");
		Serial.print("Z: ");
		Serial.print(accelData.zData);
		logger.addData("jerkPosY", "Z Acceleration (mG's)", accelData.zData);
     //*/
    ///*
		Serial.print("\tGyroscope: ");
		Serial.print("X: ");
		Serial.print(gyroData.xData);
		logger.addData("jerkPosY", "Pitch rate (dps)", gyroData.xData);
		Serial.print(" ");
		Serial.print("Y: ");
		Serial.print(gyroData.yData);
		logger.addData("jerkPosY", "Roll rate (dps)", gyroData.yData);
		Serial.print(" ");
		Serial.print("Z: ");
		Serial.print(gyroData.zData);
		logger.addData("jerkPosY", "Yaw rate (dps)", gyroData.zData);
		Serial.println(" ");
    //*/
	}
	logger.writeRow("jerkPosY");
	delay(100);
}