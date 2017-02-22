/*
 * Lidar_Manager_V2.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: Sam
 */

#include "Lidar_Manager_V2.hpp"

FRC::LidarManager::LidarManager() :

LeftFront(0),
LeftBack(1),
RightFront(2),
RightBack(3),
Lidar()

{

}

int FRC::LidarManager::getLidDistance()
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

void FRC::LidarManager::antiDavid(int offset, double slowPoint)
{
	if (getLidDistance() <= 9)
	{
		do
		{
			motorControl((getLidDistance() / slowPoint) * inputVal);
		}
		while(getLidDistance() >= 3);
	}
	else
	{
		return;
	}
}

void FRC::LidarManager::motorControl(double speed)
{
	LeftFront.Set(speed);
	LeftBack.Set(speed);
	RightFront.Set(speed);
	RightBack.Set(speed);
}
