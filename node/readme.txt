UI robotics library is a shared library designed to run on Linex or cygwin. If using sygwin 
can not be compiled as a shared library instead insert into your project. It uses a device inwhich you link or call bind to each object.  
Then when the device receives a message it send the message via vertual sockets to each component.  Then the component processes the message 
and returns a message to the device.  

Device is created with the create device function
IDevice class
	functions
		
		virtual void Release(void){};
		
			Frees all memory on device
			!!IDevice is an interface and there fore does not have a deconstructor.  Release must be called otherwise memory leaks will occur
			
		virtual void Start(void){}; 
		
			!!! Start must be called for the device to send and receive messages
			!!! You are unable to bind any objects once the device has started.  do not try unexpected results may occur.
		virtual void Bind(BindableObj* obj){};
		
			binds a bindable object pointer to the device
			one device must be bond
			
		virtual void SetServerPort(unsigned short port){};
		
			sets the port that the device will listen on
			!!! Must be called before start, otherwise unexpected results will occur
			
		virtual void Stop(void){};
		
			!!! Has not been implemented yet though it theorically should stop the device running, instead call release for now
	
	Message formatting
	
		There are two types of messages used, the old format inwhich messages have a character, 
		a command between 1 and 9, and a value between 1 and 100.  This example m1001 sets motor to forward at a power level of 1.  
		The old format is mainly used to communicate to the motor controllers and arduino because it takes up less size.
	
	New format uses the following structure
		destination: command-value
		Destination, the destination the device should send the command to.
		Command is command to be executed...
		Value is the value of the command
	
		Example:  The following command might be sent from the device to the motor component
		motor:move_forward-001  This tells the motor component to move forward and set its power level to one.
	
		!!! You can convert from the old format to the new format and visa versa by using TransToOldFormat and TransToNewFormat respectively.
		!!! You may have to update the TransToOldFormat and TransToNewFormat if you add a new command or component.
	
	msgParser.h
	
		!!!current bug occurs if you put the return value directly into a string stream it will not stream the return value 
		but the message itself
	
		FindDest returns the destination from a new formated message.
		FindCommand finds command in new format.
		FindVal finds value in new format.  Note can be picky sometimes.
		
	BindableObj.h
	
		All components inherit from bindable object.  The bindable object constructer requires one argument, the name of the component.
		This is the name the device will be looking for when the object is bond.  When object is bond the message loop will receive a message
		syncronize with the device and the other components, call hand message, sends a return value to the device, desyncronizes, and call 
		parallel message handle, and then repeats. Most of the functions in bindableobj are designed to be over riden though if you are over
		riding code you may want to copy and paste code from the bindable object source file.   Note threads are detached do not try
		to share memory between components 
			
	