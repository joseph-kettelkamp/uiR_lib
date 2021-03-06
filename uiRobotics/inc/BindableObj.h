/*
 * BindableObj.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Joseph
 */

#ifndef BINDABLEOBJ_H_
#define BINDABLEOBJ_H_

#include "../lib/tcpS/PracticalSocket.h"
#include "../inc/macro.h"
#include <exception>

namespace uiRobotics {

class BindableObj {
public:
	BindableObj(string name);
	void SetPortAndAddress(string address, unsigned short port);
	const char* getName(void);

	virtual ~BindableObj();

protected:
	virtual void HandleGetMsg(void* msg);
	virtual void HandlException(std::exception& err);

	void MsgLoop(void);
	virtual void ShutDown();
	virtual void SendMsgTo(char* address, void* msg);
private:
	TCPSocket* c_MsgClientTCP_Socket;
	std::string m_Name;
	std::thread* m_ThreadMsgRecv;
};

} /* namespace uiRobotics */

#endif /* BINDABLEOBJ_H_ */
