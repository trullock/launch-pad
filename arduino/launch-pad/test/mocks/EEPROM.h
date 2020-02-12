#ifndef EEPROM_h
#define EEPROM_h


class EEPROM_
{
public:
    EEPROM_(unsigned long size);
	void begin(int size);
    void put(int address, byte b);
    byte get(int address);
};

extern EEPROM_ EEPROM;

#endif
