/*
 * cameraManager.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: Robotics
 */
#ifndef SRC_CAMERAMANAGER_HPP_
#define SRC_CAMERAMANAGER_HPP_

#include "WPILib.h"

namespace FRC
{
	class cameraManager
	{
	public:
		cameraManager();
		void VisionThread();
	};
}
#endif /* SRC_CAMERAMANAGER_HPP_ */
