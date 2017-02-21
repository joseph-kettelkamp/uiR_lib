#include "../header/motor.h"
#define BUF_MAX 256   // default max buffer size
#define TIMEOUT 5000 // default timeout
#define DEBUG 0

motor::motor(const char* port, int baud_rate=9600) : uiRobotics::BindableObj("motor_controller")
{
	fd=-1;
	fd = serialport_init(port, baud_rate); //opening port
    (fd == -1) ? std::cout<< "couldn't open port for arduino! :(" << std::endl : std::cout<< "opened port " << port << std::endl;
    serialport_flush(fd);
}


std::string motor::HandleGetMsg(void* msg)
{

	std::string msgnew((char*)msg);
	std::string message = msgParser::TransToOldFormat(msgnew);
   std::cout<<"writing: "<<message<<std::endl;
   const char* ard_message=message.c_str();
   int rd = serialport_write(fd, ard_message);
   if(rd == -1) std::cout<<"error writing messages to arduino!" <<std::endl;

#if DEBUG //if we are debugging let's get the messages back
   	char eolchar = '\n';
   	char* buf=(char*)malloc(BUF_MAX*sizeof(char));
	  memset(buf,0,BUF_MAX); //clearing buffer
    serialport_read_until(fd, buf, eolchar, BUF_MAX, TIMEOUT); //'Arduino received <message>'
    std::cout<<"Arduino Echoed: "<<buf<<std::endl;
    free(buf);
#endif   	

    return MSG_CAN_SEND;
}
