/*
 * BindableObj.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: Joseph
 */

#include "BindableObj.h"

namespace uiRobotics {

BindableObj::BindableObj(std::string name)
	: c_MsgClientTCP_Socket(nullptr)
	, m_Name(name)
{


}

const char* BindableObj::getName()
{
	return m_Name.c_str();
}

BindableObj::~BindableObj()
{
	if(c_MsgClientTCP_Socket) delete c_MsgClientTCP_Socket;
}

} /* namespace uiRobotics */
