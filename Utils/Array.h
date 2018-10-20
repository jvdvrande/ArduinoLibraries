#ifndef __ARRAY_H
#define __ARRAY_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class FloatArray
{
public:
    FloatArray(uint8_t size);
    ~FloatArray();

    uint8_t size()                      const   {return m_size;}
    float& operator[](uint8_t index)    const   {return m_data[index];}
    
private:
    uint8_t m_size;
    float* m_data;
};

#endif // __ARRAY_H