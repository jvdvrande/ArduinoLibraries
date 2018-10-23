#include "SonarHead.h"

#include "Logger.h"

SonarHead::SonarHead(uint8_t trigger_pin, uint8_t echo_pin, uint8_t servo_pin)
    : m_sonar(trigger_pin, echo_pin)
    , m_servo_pin(servo_pin)
    , m_scans(1)
{
    init_scans(1, 0, 0);
}

void SonarHead::init()
{
    // init servo
    m_head.write(90); // look forward
    m_head.attach(m_servo_pin);

    // init sonar
    m_sonar.init();
}

void SonarHead::test_servo(int delay_ms)
{
    Logger::instance().log(0, 0, "Testing Servo   ");
    
    Logger::instance().log(0, 1, "Right           ");
    m_head.write(0);
    delay(delay_ms);
    
    Logger::instance().log(0, 1, "Forward         ");
    m_head.write(90);
    delay(delay_ms);
    
    Logger::instance().log(0, 1, "Left            ");
    m_head.write(180);
    delay(delay_ms);

    Logger::instance().log(0, 1, "Reset           ");
    m_head.write(90);

    Logger::instance().clear();
}

// ----------------------------------------------
void SonarHead::look_at(int8_t direction, bool wait)
{
    // move servo ([Right .. Left] = [-90 .. 90] -> [0 .. 180])
    int target_position = (int)direction - SERVO_MIN; 
    m_head.write(target_position);

    if (wait)
    {
        while (m_head.read() != target_position)
            delayMicroseconds(10);
    }
}

float SonarHead::scan_direction(int8_t direction, int scan_delay)
{
    look_at(direction, scan_delay == 0);
    delay(scan_delay);

    return current_distance();
}

void SonarHead::sweep(int8_t min, int8_t max, uint8_t sample_count)
{
    init_scans(sample_count, min, max);

    // scan each direction
    for (uint8_t index = 0; index < m_scans.size(); ++index)
        m_scans[index] = scan_direction(to_direction(index), 500);
}

// ----------------------------------------------
uint8_t SonarHead::to_scan_index(int8_t direction) const
{
    return (((int)direction - m_scan_min_angle) / (float)scan_range()) * (m_scans.size() - 1);
}

int8_t SonarHead::to_direction(uint8_t scan_index) const
{
    int step = scan_range() / (m_scans.size() - 1);
    return m_scan_min_angle + (scan_index * step);
}

// ----------------------------------------------
void SonarHead::init_scans(uint8_t count, int8_t min_angle, int8_t max_angle)
{
    m_scan_min_angle = min_angle;
    m_scan_max_angle = max_angle;

    m_scans = FloatArray(count);
    for (uint8_t i = 0; i < m_scans.size(); ++i)
        m_scans[i] = 0.f;
}
