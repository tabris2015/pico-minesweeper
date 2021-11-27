//
// Created by pepe on 24/11/21.
//

#ifndef PICO_MINESWEEPER_MOTOR_BTS7960_H
#define PICO_MINESWEEPER_MOTOR_BTS7960_H

#include "pico/stdlib.h"
#include <cmath>
#include "hardware/pwm.h"

#define TOP 6143    // aprox. 20.3KHz

class MotorBts7960 {
public:
    MotorBts7960(uint lpwm_pin, uint rpwm_pin);
    void write_int16(int16_t pwm) const;
    void write(float duty_cycle) const;

private:
    uint lpwm_pin_;
    uint rpwm_pin_;
    uint l_slice_num_;
    uint l_channel_;
    uint r_slice_num_;
    uint r_channel_;
};


#endif //PICO_MINESWEEPER_MOTOR_BTS7960_H
