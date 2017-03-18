/*
 * autoManager.hpp
 *
 *  Created on: Feb 20, 2017
 *      Author: tv4958
 */

#ifndef SRC_AUTOMANAGER_HPP_
#define SRC_AUTOMANAGER_HPP_

#include <inputManager.hpp>
#include <driveManager.hpp>
#include <wpilib.h>
#include <CanTalon.h>
#include "AHRS.h"
namespace FRC
{
	class autoManager
	{
		public:
		autoManager();
		Joystick Auto;
		FRC::driveManager driveManager;

		double getEncDistance();
		void driveDistance(double distance, double angle);
		void rotate(double degrees);
	};
}



#endif /* SRC_AUTOMANAGER_HPP_ */
