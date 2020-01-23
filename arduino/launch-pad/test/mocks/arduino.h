#ifndef Arduino
#define Arduino

#include <stdint.h>
#include <cstring>
#include <cstdlib>

#include "Serial.h"

// TODO: fix g++ arduino references
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1

typedef uint8_t byte;

void pinMode(int pin, int mode);
void digitalWrite(int pin, int mode);
int digitalRead(int pin);
void delay(int duration);



#endif