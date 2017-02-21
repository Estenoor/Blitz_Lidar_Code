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

int FRC::LidarManager::getDistance()
{
	Lydar->WriteBulk(LIDAR_ADDR, 2);
	Lydar->WriteBulk(&LIDAR_ADDR[2], 1);
	do
	{
		Lydar->ReadOnly(1, busyRead);
	}
	while (busyRead &! 1);
	Lydar->WriteBulk(&LIDAR_ADDR[3], 1);
	Lydar->ReadOnly(2, readData);
	return ((readData[0] * 265) + readData[1]);
}
