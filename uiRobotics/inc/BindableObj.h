/*
 * BindableObj.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Joseph
 */

#ifndef BINDABLEOBJ_H_
#define BINDABLEOBJ_H_

#include "../lib/tcpS/PracticalSocket.h"
#include <exception>

namespace uiRobotics {

class BindableObj {
public:
	BindableObj();
	void SetPortAndAddress(string address, unsigned short port);

	virtual ~BindableObj();

protected:
	virtual void HandleGetMsg(void* msg);
	virtual void HandleSendMsgTo(char* address, void* msg);
	virtual void HandlException(std::exception& err);

	virtual void ShutDown();
	virtual void SendMsgTo(char* address, void* msg);
private:
	TCPSocket* c_MsgClientTCP_Socket;
};

} /* namespace uiRobotics */

#endif /* BINDABLEOBJ_H_ */
