/*
 * arduinoManager.hpp
 *
 *  Created on: Feb 28, 2017
 *      Author: Sam
 */

#ifndef SRC_ARDUINOMANAGER_HPP_
#define SRC_ARDUINOMANAGER_HPP_

#include "WPILib.h"

namespace FRC
{
	class Arduino
	{
	private:
		I2C *arduino;

	public:
		Arduino(int deviceAddr);
		void getTemp(double receiveArray[4]);
	};
}




#endif /* SRC_ARDUINOMANAGER_HPP_ */
