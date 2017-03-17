#ifndef SRC_MANIPULATOR_HPP_
#define SRC_MANIPULATOR_HPP_

#include <CANTalon.h>
#include <DigitalInput.h>
#include <Talon.h>
#include "inputManager.hpp"


namespace FRC {

	class manipulator {
		public:
			manipulator();
			//Gear functions
			FRC::inputManager inputManager;
			CANTalon gear;
			Talon ball, climbMotor;
			DigitalInput GearSwitch;
			PowerDistributionPanel PDP;
			AnalogInput pot;

			//Gear Functions
			void GearReset(double speed);
			void GearOut(double speed);
			void ballEject();
			void climb();

		private:

	};
}



#endif




