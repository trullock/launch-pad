#ifndef IManualControl_h
#define IManualControl_h

#define ButtonEvent_None 0
#define ButtonEvent_Engaged 1
#define ButtonEvent_Disengaged 2

class IManualControl {
  public:
	  virtual ~IManualControl(){};
	  virtual char readCommand() = 0;
};

#endif