//
// Created by pepe on 25/11/21.
//

#ifndef PICO_MINESWEEPER_MINESWEEPER_H
#define PICO_MINESWEEPER_MINESWEEPER_H

#include "pico/stdlib.h"
#include "motor_bts7960.h"


#define ROBOT_MAX_LINEAR_M_S 0.3f
#define ROBOT_MIN_LINEAR_M_S (-0.3f)
#define ROBOT_MAX_ANGULAR_R_S 1.0f
#define ROBOT_MIN_ANGULAR_R_S (-1.0f)

#define ROBOT_WHEEL_SEPARATION 0.4f
#define ROBOT_WHEEL_RADIUS 0.15f


enum MotorId{
    m1,
    m2,
    m3,
    m4,
    n_motors
};

struct MinesweeperPins{
    uint lm1_lpwm;
    uint lm1_rpwm;
    uint rm1_lpwm;
    uint rm1_rpwm;
    uint lm2_lpwm;
    uint lm2_rpwm;
    uint rm2_lpwm;
    uint rm2_rpwm;
};

class Minesweeper {
public:
    Minesweeper(MinesweeperPins pins, bool has_four_motors);
    void write_motor(MotorId motor_id, float duty_cycle);
    void drive(float left, float right);
    void drive_unicycle(float v, float w);

private:
    MinesweeperPins _pins;
    MotorBts7960 _left_motor1;
    MotorBts7960 _right_motor1;
    MotorBts7960 _left_motor2;
    MotorBts7960 _right_motor2;

};


#endif //PICO_MINESWEEPER_MINESWEEPER_H
