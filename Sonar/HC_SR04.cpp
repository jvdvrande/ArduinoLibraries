#include "HC_SR04.h"

#define SIGNAL_TIME_US  2
#define TRIGGER_TIME_US 10

#define ECHO_TIMEOUT    25000L	// 25ms = 2 * 4.2875m
//#define ECHO_TIMEOUT    150000L	// 150ms

HC_SR04::HC_SR04(uint8_t trigger_pin, uint8_t echo_pin)
    : m_trigger_pin(trigger_pin)
    , m_echo_pin(echo_pin)
{
}

void HC_SR04::init()
{
    pinMode(m_trigger_pin, OUTPUT);
    pinMode(m_echo_pin,    INPUT);
}

// ----------------------------------------------
float HC_SR04::distance_avg(uint8_t wait, uint8_t count) const
{
    float min_distance = 9.f;
    float max_distance = 0.f;
    float average_sum = 0.f;
    uint8_t average_count = 0;
    float current_distance;
    
    // minimal 1 sample
    count = max(1, count);

    for (int i = 0; i < count + 2; ++i)
    {
        current_distance = distance();
        if (current_distance == 0.f)
            continue;

        // update limits
        min_distance = min(min_distance, current_distance);
        max_distance = max(max_distance, current_distance);

        // update sum
        average_sum += current_distance;
        ++average_count;

        // wait for specified interval
        delay(wait);
    }

    // calculate average (ignoring min/max values)
    if (average_count > 2)
        average_sum = (average_sum - (max_distance + min_distance)) / (average_count - 2);
    
    return average_sum;
}

// ----------------------------------------------
long HC_SR04::ping() const
{
    // make sure trigger_pin is LOW
    digitalWrite(m_trigger_pin, LOW);
    delayMicroseconds(SIGNAL_TIME_US);
    
    // set trigger_pin HIGH for 10 us
    digitalWrite(m_trigger_pin, HIGH);
    delayMicroseconds(TRIGGER_TIME_US);

    // make trigger_pin LOW again
    digitalWrite(m_trigger_pin, LOW);
    delayMicroseconds(SIGNAL_TIME_US);

    // wait for echo_pin to become HIGH and time duration (in micro_seconds) until LOW
    return pulseIn(m_echo_pin, HIGH, ECHO_TIMEOUT);
}
    
float HC_SR04::response_time_to_distance(long echo_response_us) const
{
    //*
    return (echo_response_us * RESPONE_US_TO_METER);
    /*/
    return (echo_response_us / RESPONE_US_TO_METER_INV);
    //*/
}
	



