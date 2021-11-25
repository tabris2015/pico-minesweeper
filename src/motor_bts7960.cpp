//
// Created by pepe on 24/11/21.
//

#include "motor_bts7960.h"

MotorBts7960::MotorBts7960(uint lpwm_pin, uint rpwm_pin)
: _lpwm_pin(lpwm_pin), _rpwm_pin(rpwm_pin)
{
    // init pwm
    _l_slice_num = pwm_gpio_to_slice_num(_lpwm_pin);
    _r_slice_num = pwm_gpio_to_slice_num(_rpwm_pin);
    _l_channel = pwm_gpio_to_channel(_lpwm_pin);
    _r_channel = pwm_gpio_to_channel(_rpwm_pin);

    gpio_set_function(_lpwm_pin, GPIO_FUNC_PWM);
    gpio_set_function(_rpwm_pin, GPIO_FUNC_PWM);

    pwm_set_wrap(_l_slice_num, TOP);
    pwm_set_wrap(_r_slice_num, TOP);

    pwm_set_chan_level(_l_slice_num, _l_channel, 0);
    pwm_set_chan_level(_r_slice_num, _r_channel, 0);

    pwm_set_enabled(_l_slice_num, true);
    pwm_set_enabled(_r_slice_num, true);
    //
}

void MotorBts7960::write_int16(int16_t pwm) const {
    if(pwm < 0) {
        pwm_set_chan_level(_l_slice_num, _l_channel, abs(pwm));
        pwm_set_chan_level(_r_slice_num, _r_channel, 0);
    } else {
        pwm_set_chan_level(_l_slice_num, _l_channel, 0);
        pwm_set_chan_level(_r_slice_num, _r_channel, pwm);
    }
}

void MotorBts7960::write(float duty_cycle) const {
    if(duty_cycle > 1.0f) duty_cycle = 1.0f;
    if(duty_cycle < -1.0f) duty_cycle = -1.0f;
    write_int16((int16_t)(duty_cycle * TOP));
}
