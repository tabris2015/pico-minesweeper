//
// Created by pepe on 2/12/21.
//

#include "dfrobot_dual.h"

DfRobotDual::DfRobotDual(uint m1_en_pin, uint m1_pwm_pin, uint m2_en_pin, uint m2_pwm_pin, uint16_t top)
: m1_en_pin_(m1_en_pin), m1_pwm_pin_(m1_pwm_pin), m2_en_pin_(m2_en_pin), m2_pwm_pin_(m2_pwm_pin), top_(top) {
    // init gpio
    gpio_init(m1_en_pin_);
    gpio_init(m2_en_pin_);
    gpio_set_dir(m1_en_pin_, GPIO_OUT);
    gpio_set_dir(m2_en_pin_, GPIO_OUT);

    // init pwm
    m1_slice_num_ = pwm_gpio_to_slice_num(m1_pwm_pin_);
    m1_channel_ = pwm_gpio_to_channel(m1_pwm_pin_);
    m2_slice_num_ = pwm_gpio_to_slice_num(m2_pwm_pin_);
    m2_channel_ = pwm_gpio_to_channel(m2_pwm_pin_);

    gpio_set_function(m1_pwm_pin_, GPIO_FUNC_PWM);
    gpio_set_function(m2_pwm_pin_, GPIO_FUNC_PWM);

    pwm_set_wrap(m1_slice_num_, top_);
    pwm_set_wrap(m2_slice_num_, top_);

    pwm_set_chan_level(m1_slice_num_, m1_channel_, 0);
    pwm_set_chan_level(m2_slice_num_, m2_channel_, 0);

    pwm_set_enabled(m1_slice_num_, true);
    pwm_set_enabled(m2_slice_num_, true);
}

void DfRobotDual::write_int16(int16_t level1, int16_t level2) {
    if(level1 < 0) {
        gpio_put(m1_en_pin_, true);
        pwm_set_chan_level(m1_slice_num_, m1_channel_, abs(level1));
    } else {
        gpio_put(m1_en_pin_, false);
        pwm_set_chan_level(m1_slice_num_, m1_channel_, level1);
    }

    if(level2 < 0) {
        gpio_put(m2_en_pin_, true);
        pwm_set_chan_level(m2_slice_num_, m2_channel_, abs(level2));
    } else {
        gpio_put(m2_en_pin_, false);
        pwm_set_chan_level(m2_slice_num_, m2_channel_, level2);
    }
}

void DfRobotDual::write(float pwm1, float pwm2) {
    if(pwm1 > 1.0f) pwm1 = 1.0f;
    if(pwm1 < -1.0f) pwm1 = -1.0f;
    if(pwm2 > 1.0f) pwm2 = 1.0f;
    if(pwm2 < -1.0f) pwm2 = -1.0f;
    write_int16((int16_t)(pwm1 * top_), (int16_t)(pwm2 * top_));
}
