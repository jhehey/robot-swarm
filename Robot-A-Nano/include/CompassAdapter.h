#ifndef __COMPASSADAPTER_H__
#define __COMPASSADAPTER_H__

#include <Wire.h>

#define COMPASS_ADDRESS 0x1E //0011110b, I2C 7bit address of HMC5883

float compassDeclanationAngle;

void SetupCompass(float declanationAngle = 0.22) {
	Serial.println("Setup Compass...");

	compassDeclanationAngle = declanationAngle;
	Wire.begin();  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(COMPASS_ADDRESS); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void ReadCompass(int& x, int& y, int& z, float& headingDegrees) {
  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(COMPASS_ADDRESS);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(COMPASS_ADDRESS, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }

	float heading = atan2(y, x);
	heading += compassDeclanationAngle;

  // Correct for when signs are reversed.
  if (heading < 0)
    heading += 2 * PI;

  // Check for wrap due to addition of declination.
  if (heading > 2 * PI)
    heading -= 2 * PI;

  // Convert radians to degrees for readability.
  headingDegrees = heading * 180 / M_PI;
}

#endif
