#include "../header/MenuController.h"
#include "../header/splitString.h"


void MenuController::printMainMenu()
{
	m_menu_state = main;
	std::cout<<"1) CONTROL ROBOT"<<std::endl
			 <<"2) Send Test Message To Server Without Arduino"<<std::endl
			 <<"3) Send Test Message To Server With Arduino"<<std::endl
			 <<std::endl
			 <<"input: ";
}
void MenuController::printRobotMenu()
{
	m_menu_state = robot_control;
	std::cout<<"MODE KEY: DESIRED ACTION <user input>"<<std::endl
			<<"--------------------------------------"<<std::endl
			<<"STOP ROBOT:         <0>"<<std::endl
			<<"MOVE FORWARD        <1 powerlevel>"<<std::endl
			<<"MOVE REVERSE:       <2 powerLevel>"<<std::endl
			<<"TURN RIGHT:         <3 powerLevel>"<<std::endl
			<<"TURN LEFT:          <4 powerlevel>"<<std::endl
			<<"LOWER DIGGER/BUCKET <5>"<<std::endl
			<<"RAISE DIGGER/BUCKET <6>"<<std::endl
			<<"START DIGGER        <7 powerlevel>"<<std::endl
			<<"STOP DIGGER         <8>"<<std::endl
			<<"HOLD BUCKET         <9>"<<std::endl
			<<"REQUEST SENSOR DATA <S>"<<std::endl
			<<"REQUEST IMAGE       <I>"<<std::endl
			<<std::endl
			<<"PRINT KEY           <help>"<<std::endl
			<<"EXIT MENU           <exit>"<<std::endl
			<<std::endl
			<<"input: ";
}
bool MenuController::processInput()
{
	std::string input=getInput(); //getting the input that was set in the main loop
	//std::cout<<input<<std::endl;
	if(m_menu_state == main) //if we are procesing an input to the main menu
	{
		if(!isMainInputValid(input))
		{
			std::cerr << "ERROR: invalid input\nmust be a single digit 1-3"<<std::endl;
			return false; //if the input is the incorrect level don't proccess it
		} 
		int input_switch = stoi(input); //can't switch a string so making it an int
		switch(input_switch)
		{
			case 1:
				printRobotMenu();
				break;
			case 2:
			{	
				std::string message = obtainAndFormatTestMessage();
				sendData(message);
				break;
			} //need brackets in order to set var message
			case 3:
			{
				std::string message = obtainAndFormatTestMessage();
				sendData(message);
				break;
			}
			default:
				std::cerr << "ERROR: invalid input\nmust be a single digit 1-3" << std::endl;
				return false; //did not successfully process input
				break;
		}	
		return true; //successfully processed input	
	} 
	else if (m_menu_state == robot_control) 
	{
		if(getInput() == "help") printRobotMenu();
		else if(getInput()=="exit") m_menu_state=main;
		else
		{
			if(!formatAndSend(getInput())) 
			{
				std::cout<<"ERROR: invalid input, could not send packet!"<<std::endl;
				std::cout<<std::endl<<"input: ";
				return false;
			}
		}
		std::cout<<std::endl<<"input: ";
		return true;
	}
	else
	{
		std::cerr << "FUCK SOMETHING WENT WRONG IN MENUCONTROLLER" << std::endl;
		return false;
	}
}
std::string MenuController::obtainAndFormatTestMessage(bool to_arduino)
{
	std::string packet="[T";
	std:string message;
	std::cout<<"enter message to send: ";
	getline(std::cin, message);
	std::cout<<std::endl;
	packet += to_arduino ? "A"+message : message;
	packet +="]"; //ending packet
	return packet;
}
bool MenuController::isMainInputValid(std::string input)
{
	return input.length()>1 ? false : true;
}
bool MenuController::inMainMenu()
{
	 return m_menu_state == main ?  true : false;
}
//validates and sends packet
bool MenuController::validatePowerLevel(std::vector<std::string> commands)
{
	if(commands.size()<2) return false;
	try
	{
		int powerlevel = std::stoi(commands[1]);
		return (powerlevel > 127 || powerlevel < 0) ? false : true;
	}
	catch(...) //can't convert to int
	{
		return false;
	}
}
std::string MenuController::addPadding(std::string powerlevel)
{
	if(powerlevel.length() == 1) return "00"+powerlevel;
	else if(powerlevel.length()==2) return "0"+powerlevel;
	else return powerlevel;
}
bool MenuController::formatAndSend(std::string input)
{

	std::vector<std::string> commands = splitString(input);
	if(commands.size()>2 || commands.size()==0) return false; //if the input is not the right size it's invalid

	std::string packet="[";
	if(commands[0].size()>1) return false; //mode should be one character
	char mode=commands[0].at(0);

	switch(mode) //checking if it has the correct mode
	{
		case Mode::STOP_ROBOT:
			packet+="M";
			packet.push_back(static_cast<char>(Mode::STOP_ROBOT));
			if(validatePowerLevel(commands)) return false;
			break;
		case Mode::MOVE_FORWARD:
			packet+="M";
			packet.push_back(static_cast<char>(Mode::MOVE_FORWARD));
			//std::cout<<commands[1]<<std::endl;
			if(validatePowerLevel(commands)) packet+=addPadding(commands[1]);
			else return false;
			break;
		case Mode::MOVE_REVERSE:
			packet+="M";
			packet.push_back(static_cast<char>(Mode::MOVE_REVERSE));
			if(validatePowerLevel(commands)) packet+=addPadding(commands[1]);
			else return false;
			break;
		case Mode::TURN_RIGHT:
			packet+="M";
			packet.push_back(static_cast<char>(Mode::TURN_RIGHT));
			if(validatePowerLevel(commands)) packet+=addPadding(commands[1]);
			else return false;
			break;
		case Mode::TURN_LEFT:
			packet.push_back(static_cast<char>(Mode::TURN_LEFT));
			if(validatePowerLevel(commands)) packet+=addPadding(commands[1]);
			else return false;
			break;
		case Mode::RAISE:
			packet+="M";
			packet.push_back(static_cast<char>(Mode::RAISE));
			//there should be no additional input
			if(validatePowerLevel(commands)) return false;
			break;
		case Mode::LOWER:
			packet+="M";
			packet.push_back(static_cast<char>(Mode::LOWER));
			if(validatePowerLevel(commands)) return false;
			break;
		case Mode::STOP_DIG:
			packet+="M";
			packet.push_back(static_cast<char>(Mode::STOP_DIG));
			if(validatePowerLevel(commands)) return false;
			break;
		case Mode::HOLD_BUCKET:
			packet+="M";
			packet.push_back(static_cast<char>(Mode::HOLD_BUCKET));
			if(validatePowerLevel(commands)) return false;
			break;
		case Mode::SENSOR_DATA:
			packet+="S";
			if(validatePowerLevel(commands)) return false;
			break;
		case Mode::IMAGE:
			packet+="I";
			if(validatePowerLevel(commands)) return false;
			break;									
		default:
			//std::cout<<"default"<<std::endl;
			return false;
			break;				
	}
	packet+="]";
	//std::cout<<"sending: "<<packet<<std::endl;
	sendData(packet);
	return true;
}

