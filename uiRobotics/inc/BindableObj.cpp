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
	, m_ThreadMsgRecv(nullptr)
{


}

void BindaleObj::SetPortAndAddress(string address, unsigned short port)
{

	BindaleObj this_c;
	std::copy(this_c, this);

	m_ThreadMsgRecv = new std::thread(&MsgLoop, this_c);
	c_MsgClientTCP_Socket = new TCPSocket(address, port);
};

const char* BindableObj::getName()
{
	return m_Name.c_str();
}

void BindableObj::MsgLoop()
{


	while (true)
	{
	
		c_MsgClientTCP_Socket->recv(buffer, msgMax);

		hanleMsg(buffer);
		cout << buffer << endl;

		buffer = has_to_send();
		c_MsgClientTCP_Socket->send(buffer, msgMax);

	}
}

void err()
{
	sendmsg(msg_abort);
}

BindableObj::~BindableObj()
{
	if(c_MsgClientTCP_Socket) delete c_MsgClientTCP_Socket;
}

} /* namespace uiRobotics */
