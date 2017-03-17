/*
 * cameraManager.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: Robotics
 */
#ifndef SRC_CAMERAMANAGER_HPP_
#define SRC_CAMERAMANAGER_HPP_
#include "WPILib.h"
#include "driveManager.hpp"

namespace FRC {
	class cameraManager {
	public:
		cameraManager();
		std::shared_ptr<NetworkTable> table;
		FRC::driveManager driveMan;
		double getDistFromCenter();
		void centerWithTape();
		void sendBack();
	};
}
#endif /* SRC_CAMERAMANAGER_HPP_ */
