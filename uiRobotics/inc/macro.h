/*
 * macro.h
 *
 *  Created on: Jan 29, 2017
 *      Author: Joseph
 */

#ifndef MACRO_H_
#define MACRO_H_

#include <string>
#include <sstream>

#define MSG_MAX_BUFFER_SIZE 256
#define MSG_SHUT_DOWN "system::shut_down"
#define MSG_CAN_SEND "system::can_send"

namespace msgParser
{

	string FindDesName(string msg)
	{
		std::stringstream ss(msg);
		std::string name;
		char c;

		while(ss.peek() != ':' || ss >> c)
		{
			name.push_back(c);
		};

		name.push_back('\0');

		return NULL;
	}
}

#endif /* MACRO_H_ */
