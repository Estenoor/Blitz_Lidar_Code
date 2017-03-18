/*
 * Lidar_Manager_V2.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: Sam
 */

#include "Lidar_Manager_V2.hpp"

FRC::LidarManager::LidarManager() :

Lidar() {}

//Grabs Distance values form Lidar then converts from centimeters to meters
double FRC::LidarManager::getLidDistance()
{
	Lydar->WriteBulk(LIDAR_ADDR, 2);
	Lydar->WriteBulk(&LIDAR_ADDR[2], 1);
	do
	{
		Lydar->ReadOnly(1, busyRead);
	}
	while ((int)busyRead & 0x01);
	Lydar->WriteBulk(&LIDAR_ADDR[3], 1);
	Lydar->ReadOnly(2, readData);
	int distCent = ((readData[0] * 265) + readData[1]);
	return (distCent / 100); //Converts centimeters into meters
}

//Returns Limit for Speed Input to Motor
double FRC::LidarManager::ProportionalSlowAntiDavid()
{	double startLimit = 9;
	double endLimit = 3;
	double range = startLimit - endLimit;
	double output;
	double distance = getLidDistance();
	double processVariable = distance - endLimit;
	if (distance <= 9 && distance >= 3)
	{
		output = (processVariable / range);
	}
	else if(processVariable > 9)
	{
		output = 1;
	}
	else
	{
		output = 0;
	}

	return output;
}
