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

void FRC::LidarManager::ProportionalSlowAntiDavid(double setPoint, double proportionalGain, double speed)
{
	if (getLidDistance() <= 9)
	{
		do
		{
			int processVariable = getLidDistance();
			double error = setPoint - processVariable;
			double output = (proportionalGain * error) * (-1 * speed);
			driveManager.mecanumDrive(0, output, 0.00, true);
		}
		while(getLidDistance() >= 3);
		driveManager.mecanumDrive(0, 0, 0, true);
	}
}

//Stops Robot from running into a wall/flat surface
void FRC::LidarManager::antiDavid(int offset, double slowPoint)
{
	if (getLidDistance() <= 9)
	{
		do
		{
			SmartDashboard::PutBoolean("IsLidar", true);
			SmartDashboard::PutNumber("Lidar", getLidDistance());
			double xVal = ((getLidDistance() / slowPoint));
			driveManager.mecanumDrive(0, xVal, 0.00, true);
			SmartDashboard::PutNumber("xVal", xVal);
		}
		while(getLidDistance() >= 3);
		driveManager.mecanumDrive(0, 0, 0, true);
	}
}

/*
void Autonomous()
{
	while (IsEnabled() && IsAutonomous())
	{
		bool isAuto = true;
		SmartDashboard::PutBoolean("isAuto", isAuto);
		Lidar.ProportionalSlowAntiDavid(3, 1.2, 0.5);

	}
}

/**/
