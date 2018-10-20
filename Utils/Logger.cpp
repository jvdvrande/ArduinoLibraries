#include "Logger.h"

Logger& Logger::instance()
{
    static Logger s_logger;
    return s_logger;
}

Logger::Logger()
    : m_lcd(0x27, 16, 2)    // set the LCD address to 0x27 for a 16 chars and 2 line display 
{
    // initialize the lcd
    m_lcd.init();
    m_lcd.backlight(); 
}

// ----------------------------------------------
void Logger::log(float number, const char* unit)
{
    m_lcd.print(number);
    m_lcd.print(' ');
    m_lcd.print(unit);
}

void Logger::log(uint8_t col, uint8_t row, const String& text)
{
    m_lcd.setCursor(col, row);
    m_lcd.print(text);
}

void Logger::log(uint8_t col, uint8_t row, const char* text)
{
    m_lcd.setCursor(col, row);
    m_lcd.print(text);
}
