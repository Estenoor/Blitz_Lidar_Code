/*
 * Lidar_Manager.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: Sam
 */

#include "Lidar_Manager.hpp"

FRC::LidarManager::LidarManager() :

Lidar()
{

}

//This Function Grabs All of the Data from the Lidar_Arduino
void FRC::LidarManager::getAllDistance()
{
	Lydar_Arduino->WriteBulk(getAllData, 1);

	Lydar_Arduino->ReadOnly(10, &rawDistanceBytes[0]);
	Lydar_Arduino->ReadOnly(10, &rawDistanceBytes[10]);
	Lydar_Arduino->ReadOnly(10, &rawDistanceBytes[20]);
	Lydar_Arduino->ReadOnly(10, &rawDistanceBytes[30]);
	Lydar_Arduino->ReadOnly(10, &rawDistanceBytes[40]);
	Lydar_Arduino->ReadOnly(10, &rawDistanceBytes[50]);
	Lydar_Arduino->ReadOnly(10, &rawDistanceBytes[60]);
	Lydar_Arduino->ReadOnly(4,  &rawDistanceBytes[70]);

	int y = 0;
	int z = 1;
	for (int x = 0; x < 37; x++)
	{
		arduinoData[x] = ((rawDistanceBytes[y] * 256) + rawDistanceBytes[z]);
		z += 2;
		y += 2;
	}
}

int FRC::LidarManager::getAngleDistance(double angle)
{
	int position = ((angle - 45) / 2.5);
	getAngleData[1] = position;
	Lydar_Arduino->WriteBulk(getAngleData, 2);

	Lydar_Arduino->ReadOnly(2, readData);
	return ((readData[1] * 256) + readData[1]);
}

void FRC::LidarManager::convertData(double startAngle, bool allData)
{
	for(int x = 0; x < 37; x++)
	{
		pairedData[0][x] = (arduinoData[x] * cos(startAngle) * 2.54);
		pairedData[1][x] = (arduinoData[x] * sin(startAngle) * 2.54);
		startAngle += 2.5;
	}


}

bool FRC::LidarManager::antiDavid()
{
	Lidar->getAllDistance();
	Wait(0.005);
	Lidar->convertData(45, true);
	if(pairedData[0][18] <= 12)
	{
		return true;
	}
	else
	{
		return false;
	}
}

