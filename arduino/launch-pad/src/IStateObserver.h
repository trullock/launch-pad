#ifndef IStateObserver_h
#define IStateObserver_h

class IStateObserver {
  public:
	  virtual ~IStateObserver(){};
	  virtual bool interlockEngaged() = 0;
	  virtual bool firingMechanismEngaged() = 0;
	  virtual float batteryVoltage() = 0;
};

#endif