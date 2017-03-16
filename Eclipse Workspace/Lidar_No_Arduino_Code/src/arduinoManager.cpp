/*
 * arduinoManager.cpp
 *
 *  Created on: Feb 28, 2017
 *      Author: Sam
 */
#include "WPILib.h"
#include "arduinoManager.hpp"

FRC::Arduino::Arduino(int deviceAddr)
{
	arduino = new I2C(I2C::kOnboard, deviceAddr);
}

void FRC::Arduino::getTemp(double receiveArray[4])
{
	arduino->ReadOnly(4, (uint8_t*)receiveArray);
	for (int i = 0; i < 4; i++)
	{
		receiveArray[i] = receiveArray[i] / 10;
	}
}


