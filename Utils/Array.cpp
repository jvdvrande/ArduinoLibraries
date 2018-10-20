#include "Array.h"

FloatArray::FloatArray(uint8_t size)
{
    // minimum size = 1
    m_size = max(1, size);
    m_data = new float[m_size];   
}

FloatArray::~FloatArray()
{
    delete m_data;
}