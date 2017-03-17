/*
 * autoManager.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: tv4958
 */
#include <autoManager.hpp>
#include <Joystick.h>
#include <Timer.h>
#include <cmath>
#include <cstdbool>
#include <cstdlib>
#include <inputManager.hpp>
#include <driveManager.hpp>
#include <WPILib.h>
#include <CanTalon.h>
#include "AHRS.h"

FRC::autoManager::autoManager() :

driveManager(),
Auto(3)

{

}

double FRC::autoManager::getEncDistance(){
	double leftFront = (driveManager.leftFrontM.GetEncPosition()/3024)* 2.0943951024;
	double leftBack = (driveManager.leftBackM.GetEncPosition()/3024)* 2.0943951024;
	double rightFront = -((driveManager.rightFrontM.GetEncPosition()/3024)* 2.0943951024);
	double rightBack = -((driveManager.rightBackM.GetEncPosition()/3024)* 2.0943951024);

	SmartDashboard::PutNumber("leftFront", leftFront);
	SmartDashboard::PutNumber("leftBack", leftBack);
	SmartDashboard::PutNumber("rightFront", rightFront);
	SmartDashboard::PutNumber("rightBack", rightBack);

	double distance = (leftFront + leftBack + rightFront + rightBack)/4;
	SmartDashboard::PutNumber("dist", distance);
	return distance;
}


void FRC::autoManager::driveDistance(double distance, double angle){
	if(distance > getEncDistance()){
		driveManager.mecanumDrive(0, .3, 0, false);
		//driveManager.straightDrive(angle, 0, .5);
	}else{
		driveManager.mecanumDrive(0, 0, 0, false);
		//driveManager.straightDrive(angle, 0, 0);
	}
}

void FRC::autoManager::rotate(double degrees){
	if(driveManager.getAngle() < degrees-2  && driveManager.getAngle() > (degrees - 180)){
		driveManager.mecanumDrive(0, 0, .3, false);
	}else if(driveManager.getAngle() < degrees-2  && driveManager.getAngle() < (degrees - 180)){
		//mecanumDrive(0, 0, -.3, false);
	}else{
		driveManager.mecanumDrive(0, 0, 0, false);
	}
}
