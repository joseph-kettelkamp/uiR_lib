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
#include <atomic>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <map>

class Device : public uiRobotics::IDevice{
public:
	//must use pool to deallocal localPort
	Device(char* localPort);

	//overrides IDevice
	virtual void Release(void);
	virtual void Start(void);
	virtual void Bind(uiRobotics::BindableObj* obj);
	virtual void Stop(void);
	// end

	virtual ~Device(void);
protected:
	virtual void msgSenderLoop(void);

private:
	std::atomic<bool> m_Running;
	std::thread* m_msgSenderThread;
	TCPServerSocket* s_LocalTCP_Socket;
	unsigned short m_Port;
	std::map<char*, TCPSocket*, std::less<char*>> m_BoundObj;
};

#endif /* DEVICE_H_ */
