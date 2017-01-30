/*
 * Device.h
 *
 *  Created on: Jan 26, 2017
 *      Author: Joseph
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include "../inc/IDevice.h"
#include "../lib/tcpS/PracticalSocket.h"
#include "../inc/BindableObj.h"
#include "../inc/macro.h"
#include <atomic>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <map>
#include <stdio.h>
#include <unistd.h>

struct BoundObject
{
	uiRobotics::BindableObj* obj;
	TCPSocket* socket;
};

class Device : public uiRobotics::IDevice{
public:
	//must use pool to deallocal localPort
	Device(char* localPort);

	//overrides IDevice
	virtual void Release(void);
	virtual void Start(void);
	virtual void SetServerPort(unsigned short port);
	virtual void Bind(uiRobotics::BindableObj* obj);
	virtual void shutDown(void);
	virtual void Stop(void);
	// end

	virtual ~Device(void);
protected:
	virtual void msgSenderLoop(void);
	virtual bool isSendBackGood(std::string sendBack);

private:
	std::atomic<bool> m_Running;
	std::thread* m_msgSenderThread;
	TCPServerSocket* s_LocalTCP_Socket;

	unsigned short m_Port;
	std::map<char*, BoundObject, std::less<char*>> mc_BoundObj;
	unsigned short mc_RecvPort;
};

#endif /* DEVICE_H_ */
