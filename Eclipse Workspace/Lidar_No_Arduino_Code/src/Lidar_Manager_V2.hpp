/*
 * Lidar_Manager_V2.hpp
 *
 *  Created on: Feb 20, 2017
 *      Author: Sam
 */

#ifndef SRC_LIDAR_MANAGER_V2_HPP_
#define SRC_LIDAR_MANAGER_V2_HPP_

#include "WPILib.h"
#include "CANTalon.h"
#include "math.h"
#include "inputManager.hpp"
#include "driveManager.hpp"

namespace FRC
{
	class LidarManager
	{
	private:
		CANTalon LeftFront;
		CANTalon LeftBack;
		CANTalon RightFront;
		CANTalon RightBack;
		FRC::driveManager driveManager;
		FRC::LidarManager *Lidar;
		I2C *Lydar = new I2C(I2C::kOnboard, 0x62);
		uint8_t LIDAR_ADDR[4] {0x00, 0x04, 0x01, 0x8f};
		uint8_t busyRead[1];
		uint8_t readData[2];
		const double inputVal = -1;

	public:
		LidarManager();
		double getLidDistance();
		void antiDavid(int offset, double slowPoint);
		void ProportionalSlowAntiDavid(double setPoint, double proportionalGain, double speed);
	};
}


#endif /* SRC_LIDAR_MANAGER_V2_HPP_ */
