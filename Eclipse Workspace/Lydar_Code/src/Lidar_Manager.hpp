/*
 * Lydar_Manager.hpp
 * Controls RoboRio to Arduino Communication for LidarLiteV3
 *
 * Created on: Feb 2, 2017
 *	   Author: Sam Ferguson
 *
 */

#ifndef SRC_LIDAR_MANAGER_HPP_
#define SRC_LIDAR_MANAGER_HPP_

#include "WPILib.h"
#include "math.h"

namespace FRC
{
	class LidarManager
	{
	private:
		FRC::LidarManager *Lidar;
		I2C *Lydar_Arduino = new I2C(I2C::kOnboard, 0x73);

		int arduinoData[37];
		uint8_t rawDistanceBytes[74];
		uint8_t readData[2];

		uint8_t getAngleData[2] {0x02};
		uint8_t getAllData[1] {0x01};

	public:
		LidarManager();

		double pairedData[2][37];

		void configure(int configuration);
		void getAllDistance();
		int getAngleDistance(double angle);
		void convertData(double startAngle, bool allData);
		bool antiDavid();
	};
}

#endif /* SRC_LIDAR_MANAGER_HPP_ */
