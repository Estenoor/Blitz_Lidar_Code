/*
 * DashboardManager.hpp
 *
 *  Created on: Mar 18, 2017
 *      Author: Sam
 */

#ifndef SRC_DASHBOARDMANAGER_HPP_
#define SRC_DASHBOARDMANAGER_HPP_

#include "WPILib.h"
#include "inputManager.hpp"
#include "driveManager.hpp"
#include "manipulator.hpp"
#include "cameraManager.hpp"
#include "autoManager.hpp"
#include "Lidar_Manager_V2.hpp"

namespace FRC
{
	class DashboardManager
	{
	private:
		FRC::inputManager inputMan;
		FRC::driveManager driveMan;
		FRC::manipulator manipulator;
		FRC::autoManager autoMan;
		FRC::LidarManager lidarMan;
		FRC::cameraManager cameraMan;


	public:
		DashboardManager();
		void autoSmartDashboard();
		void teleSmartDashboard();
		void rawInputSmartDashboard();
	};
}




#endif /* SRC_DASHBOARDMANAGER_HPP_ */
