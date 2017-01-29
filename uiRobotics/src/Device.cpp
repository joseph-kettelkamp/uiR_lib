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
	shutDown();
	m_Running.store(false, std::memory_order_seq_cst);
	m_msgSenderThread->join();
	delete m_msgSenderThread;
}

void Device::Bind(uiRobotics::BindableObj* obj)
{
	string address = s_LocalTCP_Socket->getLocalAddress();
	unsigned short port = s_LocalTCP_Socket->getLocalPort();

	pid_t pid = std::fork();

	TCPSocket* sock;
	std::atomic<bool> canCreateClientSocket;


	if (pid == 0)
	{
		bool exchange = true;
		while (canCreateClientSocket.compare_exchange_strong(exchange, true, std::memory_order_seq_cst))
		{
			exchange = true;
		}
		std::sleep(1000.0f);

		obj->SetPortAndAddress(address, port);
	}
	else if (pid > 0)
	{
		canCreateClientSocket.store(true, std::memory_order_seq_cst);
		sock = s_LocalTCP_Socket->accept();
	}
	else (pid == -1)
	{
		std::cerr << "fork() failded Device::Bind() " << std::endl;
		std::exit(0x1);
	}

	m_BoundObj->insert(m_Name, obj);

}

void Device::msgSenderLoop()
{

	bool exchange = true;
	while(m_Running.compare_exchange_strong(exchange, true, std::memory_order_seq_cst))
	{
		exchange = true;


		getMsgCode go here

		map<char*, uiRobotics::BindableObj, std::less<char*>>::iterater it++;
		for (; it->first != nullptr, it++)
		{

			string name(it->first);
			if (name = msgName)
			{
				it->second.socket->send(msg, bufferSize);

				//wait for recv msg back form client

				it->second.socket->recv(recvMsg, bufferSize);
				if (!isSendBackGood(recvMsg))
					shutDown();
			}
		}
	}
}

bool Device::isSendBackGood(std::string sendBack)
{

	return sendBack != MSG_SHUT_DOWN;
}

Device::shutDown()
{

	for (; it->first != nullptr; it++)
	{
		it->second.socket->send(MSG_ABORT, bufferSize);
	}
}

Device::~Device()
{
	bool running = m_Running.load(std::memory_order_seq_cst);
	if(running)
		Stop();


	for ()
	{
	
		it->second.socket->clenUP();
		delete it->second.socket;
	}
	delete s_LocalTCP_Socket;
}

