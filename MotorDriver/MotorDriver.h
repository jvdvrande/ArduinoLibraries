#ifndef __MOTOR_DRIVER_H
#define __MOTOR_DRIVER_H

#include "Arduino.h"

class MotorDriver
{
public:
    MotorDriver(uint8_t rpwm, uint8_t rfwd, uint8_t rbwd, uint8_t lpwm, uint8_t lfwd, uint8_t lbwd);

    void init();

    void set_drive_pwm(uint8_t pwm)         {m_drive_pwm = pwm;}
    void set_turn_pwm(uint8_t pwm)          {m_turn_pwm = pwm;}

public:
    void forward()                      {forward(m_drive_pwm);}
    void forwardF(float factor)         {forward(factor * m_drive_pwm);}
    void forward(uint8_t pwm);

    void backward()                     {backwardF(0.5f);}
    void backwardF(float factor)        {backward(factor * m_drive_pwm);}
    void backward(uint8_t pwm);
    void backward_for(uint16_t delay_ms);

    void stop();
    
public:
    void turn_right()               {turn_right(m_turn_pwm);}
    void turn_right(uint8_t pwm);
    void turn_left()                {turn_left(m_turn_pwm);}
    void turn_left(uint8_t pwm);    

    void test_drives(uint8_t pwm, int drive_delay, int pause_delay);

private:
    void drive_right(bool fwd, uint8_t speed);
    void drive_left(bool fwd, uint8_t speed);
    
private:
    // output pins
    uint8_t m_left_pwm_pin;
    uint8_t m_left_fwd_pin;
    uint8_t m_left_bwd_pin;

    uint8_t m_right_pwm_pin;
    uint8_t m_right_fwd_pin;
    uint8_t m_right_bwd_pin;

    // pwm
    uint8_t m_drive_pwm;
    uint8_t m_turn_pwm;
};

#endif // __MOTOR_DRIVER_H