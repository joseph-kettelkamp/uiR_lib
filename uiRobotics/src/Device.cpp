/*
 * Device.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Joseph
 */

#include "../header/Device.h"

Device::Device(char* localPort) : uiRobotics::IDevice()
	,m_Running(false)
	,m_msgSenderThread(nullptr)
	,s_LocalTCP_Socket(nullptr)
	,m_Port(std::atoi(localPort))
{
	s_LocalTCP_Socket = new TCPServerSocket(m_Port);
}

void Device::Release()
{
	this->~IDevice();
}

void Device::Start()
{
	m_Running.store(true, std::memory_order_seq_cst);
	m_msgSenderThread = new std::thread(&Device::msgSenderLoop, this);
}

void Device::Stop()
{
	m_Running.store(false, std::memory_order_seq_cst);
	m_msgSenderThread->join();
	delete m_msgSenderThread;
}

void Device::Bind(uiRobotics::BindableObj* obj)
{
	string address = s_LocalTCP_Socket->getLocalAddress();
	unsigned short port = s_LocalTCP_Socket->getLocalPort();

	obj->SetPortAndAddress(address, port);

}

void Device::msgSenderLoop()
{

	bool exchange = true;
	while(m_Running.compare_exchange_strong(exchange, true, std::memory_order_seq_cst))
	{
		exchange = true;

	}
}

Device::~Device()
{
	bool running = m_Running.load(std::memory_order_seq_cst);
	if(running)
		Stop();

	delete s_LocalTCP_Socket;
}

