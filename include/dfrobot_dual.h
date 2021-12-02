//
// Created by pepe on 2/12/21.
//

#ifndef PICO_MINESWEEPER_DFROBOT_DUAL_H
#define PICO_MINESWEEPER_DFROBOT_DUAL_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

class DfRobotDual {
public:
    DfRobotDual(uint m1_en_pin, uint m1_pwm_pin, uint m2_en_pin, uint m2_pwm_pin, uint16_t top);
    void write_int16(int16_t level1, int16_t level2);
    void write(float pwm1, float pwm2);

private:
    uint m1_en_pin_;
    uint m1_pwm_pin_;
    uint m2_en_pin_;
    uint m2_pwm_pin_;
    uint16_t top_;
    uint m1_slice_num_;
    uint m1_channel_;
    uint m2_slice_num_;
    uint m2_channel_;
};


#endif //PICO_MINESWEEPER_DFROBOT_DUAL_H
