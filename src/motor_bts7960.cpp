//
// Created by pepe on 24/11/21.
//

#include "motor_bts7960.h"

MotorBts7960::MotorBts7960(uint lpwm_pin, uint rpwm_pin)
: lpwm_pin_(lpwm_pin), rpwm_pin_(rpwm_pin)
{
    // init pwm
    l_slice_num_ = pwm_gpio_to_slice_num(lpwm_pin_);
    r_slice_num_ = pwm_gpio_to_slice_num(rpwm_pin_);
    l_channel_ = pwm_gpio_to_channel(lpwm_pin_);
    r_channel_ = pwm_gpio_to_channel(rpwm_pin_);

    gpio_set_function(lpwm_pin_, GPIO_FUNC_PWM);
    gpio_set_function(rpwm_pin_, GPIO_FUNC_PWM);

    pwm_set_wrap(l_slice_num_, TOP);
    pwm_set_wrap(r_slice_num_, TOP);

    pwm_set_chan_level(l_slice_num_, l_channel_, 0);
    pwm_set_chan_level(r_slice_num_, r_channel_, 0);

    pwm_set_enabled(l_slice_num_, true);
    pwm_set_enabled(r_slice_num_, true);
    //
}

void MotorBts7960::write_int16(int16_t pwm) const {
    if(pwm < 0) {
        pwm_set_chan_level(l_slice_num_, l_channel_, abs(pwm));
        pwm_set_chan_level(r_slice_num_, r_channel_, 0);
    } else {
        pwm_set_chan_level(l_slice_num_, l_channel_, 0);
        pwm_set_chan_level(r_slice_num_, r_channel_, pwm);
    }
}

void MotorBts7960::write(float duty_cycle) const {
    if(duty_cycle > 1.0f) duty_cycle = 1.0f;
    if(duty_cycle < -1.0f) duty_cycle = -1.0f;
    write_int16((int16_t)(duty_cycle * TOP));
}
