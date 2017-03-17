/*
 * cameraManager.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: Robotics
 */
#include "WPILib.h"
#include "cameraManager.hpp"

FRC::cameraManager::cameraManager() :
	table(),
	driveMan()
{
	table = NetworkTable::GetTable("SmartDashboard");
}

double FRC::cameraManager::getDistFromCenter() {
	table = NetworkTable::GetTable("SmartDashboard");
	return table->GetNumber("CENTER", -1) - 240;
}

void FRC::cameraManager::centerWithTape() {
	while(!(getDistFromCenter() > -10 && getDistFromCenter() < 10)) {
		if (getDistFromCenter() > 10) {
			driveMan.mecanumDrive(-.2, 0, 0, false);
		}
		if (getDistFromCenter() < -10) {
			driveMan.mecanumDrive(.2, 0, 0, false);
		}
	}
	driveMan.mecanumDrive(0, 0, 0, false);
}

void FRC::cameraManager::sendBack() {
	table = NetworkTable::GetTable("SmartDashboard");
	table->PutNumber("CENTER2", table->GetNumber("RUN_TIME", -1));
}
