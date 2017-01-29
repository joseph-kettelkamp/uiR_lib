/*
 * BindableObj.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: Joseph
 */

#include "BindableObj.h"

namespace uiRobotics {

BindableObj::BindableObj()
	: c_MsgClientTCP_Socket(nullptr)
{


}

BindableObj::~BindableObj()
{
	if(c_MsgClientTCP_Socket) delete c_MsgClientTCP_Socket;
}

} /* namespace uiRobotics */
