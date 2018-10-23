#ifndef __HC_SR04_H
#define __HC_SR04_H

#include "Arduino.h"

// 343 m/s
#define SOUND_SPEED 343.f

// 0.000343 m/us (response time is two-way, sound travels the distance twice)
#define RESPONE_US_TO_METER     0.0001715f
// 1.f/RESPONE_US_TO_METER to overcome float-precision errors
#define RESPONE_US_TO_METER_INV 5830.90f

class HC_SR04
{
public:
	HC_SR04(uint8_t trigger_pin, uint8_t echo_pin);

    void init();
    
public:
	float distance()            const {return response_time_to_distance(ping());}
	float distance_avg(uint8_t wait = 2, uint8_t count = 5) const;

private:
    // returns echo-response time in microseconds 
    long ping() const;

	// Do the measurement calculation and return distance in meter
	float response_time_to_distance(long echo_response_us)        const;

private:
    uint8_t m_trigger_pin;
	uint8_t m_echo_pin;
};

#endif  // __HC_SR04_H