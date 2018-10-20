#include "MotorDriver.h"

MotorDriver::MotorDriver(uint8_t rpwm, uint8_t rfwd, uint8_t rbwd, uint8_t lpwm, uint8_t lfwd, uint8_t lbwd)
{
    m_left_pwm_pin = lpwm;
    m_left_fwd_pin = lfwd;
    m_left_bwd_pin = lbwd;
    m_right_pwm_pin = rpwm;
    m_right_fwd_pin = rfwd;
    m_right_bwd_pin = rbwd;
    
    m_drive_pwm = 200;
    m_turn_pwm  = 100;

    init();
}

void MotorDriver::forward(uint8_t pwm)
{
    drive_right(true, pwm);
    drive_left (true, pwm);
}

void MotorDriver::backward(uint8_t pwm)
{
    drive_right(false, pwm);
    drive_left (false, pwm);
}

void MotorDriver::stop()
{
    analogWrite(m_right_pwm_pin, 0);
    analogWrite(m_left_pwm_pin,  0);

    digitalWrite(m_right_fwd_pin, LOW);
    digitalWrite(m_right_bwd_pin, LOW);
    digitalWrite(m_left_fwd_pin,  LOW);
    digitalWrite(m_left_bwd_pin,  LOW);
}

// ----------------------------------------------

void MotorDriver::turn_right(uint8_t pwm)
{
    drive_right(true,  pwm);
    drive_left (false, pwm);
}

void MotorDriver::turn_left(uint8_t pwm)
{
    drive_right(false, pwm);
    drive_left (true,  pwm);
}

// ----------------------------------------------

void MotorDriver::test_drives(uint8_t pwm, int drive_delay, int pause_delay)
{
    drive_left(true, pwm);
    delay(drive_delay);
    stop();
    delay(pause_delay);

    drive_right(true, pwm);
    delay(drive_delay);
    stop();
    delay(pause_delay);
    
    drive_left(false, pwm);
    delay(drive_delay);
    stop();
    delay(pause_delay);
    
    drive_right(false, pwm);
    delay(drive_delay);
    stop();
    delay(pause_delay);
}

// ----------------------------------------------
void MotorDriver::init()
{
    // setup pins
    pinMode(m_left_pwm_pin, OUTPUT);
    pinMode(m_left_fwd_pin, OUTPUT);
    pinMode(m_left_bwd_pin, OUTPUT);
    
    pinMode(m_right_pwm_pin, OUTPUT);
    pinMode(m_right_fwd_pin, OUTPUT);
    pinMode(m_right_bwd_pin, OUTPUT);
}

void MotorDriver::drive_right(bool fwd, uint8_t pwm)
{
    digitalWrite(m_right_fwd_pin, fwd ? HIGH : LOW);
    digitalWrite(m_right_bwd_pin, fwd ? LOW  : HIGH);

    analogWrite(m_right_pwm_pin, pwm);
}

void MotorDriver::drive_left(bool fwd, uint8_t pwm)
{
    digitalWrite(m_left_fwd_pin, fwd ? HIGH : LOW);
    digitalWrite(m_left_bwd_pin, fwd ? LOW  : HIGH);

    analogWrite(m_left_pwm_pin, pwm);
}