#ifndef IManualControl_h
#define IManualControl_h

#define ButtonEvent_None 0
#define ButtonEvent_Engaged 1
#define ButtonEvent_Disengaged 2

class IManualControl {
  public:
	  virtual ~IManualControl(){};
	  virtual bool arm() = 0;
	  virtual int armButtonEvent() = 0;
	  virtual int fireButtonEvent() = 0;
};

#endif