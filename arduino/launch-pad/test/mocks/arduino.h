#ifndef Arduino
#define Arduino

#include <stdint.h>
#include <cstring>
#include <cstdlib>

#include "Serial.h"

// Fix arduino references. These are probably not real/correct values but it shouldnt metter for these tests
#define HIGH 1
#define LOW 0
#define INPUT 0
#define INPUT_PULLUP 2
#define OUTPUT 1
#define A0 -1

typedef uint8_t byte;

void pinMode(int pin, int mode);
void digitalWrite(int pin, int mode);
int digitalRead(int pin);
int analogRead(int pin);
void delay(int duration);



#endif