#ifndef __LOGGER_H
#define __LOGGER_H

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Logger
{
    Logger();

public:
    static Logger& instance();

    void clear()                                {m_lcd.clear();}
    
public:
    void log(const String& text)                {m_lcd.print(text);}
    void log(const char* text)                  {m_lcd.print(text);}
    void log(float number)                      {m_lcd.print(number);}
    void log(float number, const char* unit);

    void log(uint8_t col, uint8_t row, const char* text);

private:
    LiquidCrystal_I2C m_lcd;
};

#endif // __LOGGER_H