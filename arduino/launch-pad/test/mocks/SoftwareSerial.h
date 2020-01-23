#ifndef SoftwareSerial_h
#define SoftwareSerial_h


class SoftwareSerial
{

public:
  SoftwareSerial(uint8_t receivePin, uint8_t transmitPin);
  void begin(long speed);
  void write(uint8_t byte);
  char read();
  int available();
};

#endif
