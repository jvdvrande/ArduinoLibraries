#ifndef __SONAR_HEAD_H
#define __SONAR_HEAD_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Array.h"
#include "HC_SR04.h"
#include "Servo.h"

#define SERVO_MIN   -90
#define SERVO_MAX    90

class SonarHead
{
public:
    enum Direction
    {
        Right   = -90,
        Forward = 0,
        Left    = 90,

        Range   = 180
    };

public:
	SonarHead(uint8_t trigger_pin, uint8_t echo_pin, uint8_t servo_pin);

    void look_at(int8_t direction, bool wait);
    
    float current_distance()                const   {return m_sonar.distance();}
    int current_direction()                         {return m_head.read() + SERVO_MIN;}

    float scan_direction(int8_t direction, int scan_delay = 0);

    // do number of scans in defined range 
    void sweep(int8_t min, int8_t max, uint8_t sample_count);

    uint8_t scan_count()                        const   {return m_scans.size();}
    uint8_t scan_range()                        const   {return (int)m_scan_max_angle - m_scan_min_angle;}
    float scanned_distance(int8_t direction)    const   {return m_scans[to_scan_index(direction)];}

    uint8_t to_scan_index(int8_t direction)     const;
    int8_t to_direction(uint8_t scan_index)     const;
    
private:
    void init_scans(uint8_t count, int8_t min_angle, int8_t max_angle);

private:
    HC_SR04 m_sonar;
    Servo m_head;

    // scan results
    FloatArray m_scans;
    int8_t m_scan_min_angle;
    int8_t m_scan_max_angle;
};

#endif // __SONAR_HEAD_H



