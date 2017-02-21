/*
 * test.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: JJB07
 */

//#include <iostream>
#include "inc/IDevice.h"
#include <iostream>
#include "lib/TransToOldFormat/msgParser.h"
#include "header/motor.h"

int main()
{
	std::cout << "working" << std::endl;

	uiRobotics::IDevice* dev;
	char str[] = "6000";
	uiRobotics::CREATE_UI_ROBOTICS_DEVICE(&dev, str);
	motor motor("address", 9600);

	dev->Bind(&motor);
	dev->SetServerPort(7001);

	dev->Start();
	TCPServerSocket sock(7000);

	TCPSocket* s = sock.accept();
	TCPSocket revS("0.0.0.0", 7001);
	char buffer[255];
	while(true)
	{

		s->recv(buffer, 255);

		std::string str = msgParser::TransToNewFormat(std::string(buffer));
		std::cout << str << std::endl;
		std::cout << msgParser::TransToOldFormat(str) << std::endl;

		revS.send(str.c_str(), MSG_MAX_BUFFER_SIZE);
		char buffer[MSG_MAX_BUFFER_SIZE];
		revS.recv(buffer, MSG_MAX_BUFFER_SIZE);
		/*while(true)
		{
			this_thread::yield();
		}*/
	}
}
