/*
 * start.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Joseph
 */
#include "../inc/IDevice.h"
#include "../header/Device.h"

namespace uiRobotics
{

	void CREATE_UI_ROBOTICS_DEVICE(IDevice** dev, char* localPort)
	{
		*dev = new Device(localPort);
	}

}

