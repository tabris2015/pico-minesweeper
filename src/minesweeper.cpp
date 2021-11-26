//
// Created by pepe on 25/11/21.
//

#include "minesweeper.h"

Minesweeper::Minesweeper(MinesweeperPins pins, bool has_four_motors)
:
_pins(pins),
_left_motor1(_pins.lm1_lpwm, _pins.lm1_rpwm),
_right_motor1(_pins.rm1_lpwm, _pins.rm1_rpwm),
_left_motor2(_pins.lm2_lpwm, _pins.lm2_rpwm),
_right_motor2(_pins.rm2_lpwm, _pins.rm2_rpwm)
{
    drive(0, 0);
}

void Minesweeper::write_motor(MotorId motor_id, float duty_cycle) {
    switch (motor_id) {
        case MotorId::m1:
            _left_motor1.write(duty_cycle);
            break;
        case MotorId::m2:
            _right_motor1.write(duty_cycle);
            break;
        case MotorId::m3:
            _left_motor2.write(duty_cycle);
            break;
        case MotorId::m4:
            _right_motor2.write(duty_cycle);
            break;
        default:
            break;
    }
}

void Minesweeper::drive(float left, float right) {
    _left_motor1.write(left);
    _right_motor1.write(right);
    _left_motor2.write(left);
    _right_motor2.write(right);
}

void Minesweeper::drive_unicycle(float v, float w) {
    if(v > ROBOT_MAX_LINEAR_M_S) v = ROBOT_MAX_LINEAR_M_S;
    if(v < ROBOT_MIN_LINEAR_M_S) v = ROBOT_MIN_LINEAR_M_S;
    if(w > ROBOT_MAX_ANGULAR_R_S) w = ROBOT_MAX_ANGULAR_R_S;
    if(w < ROBOT_MIN_ANGULAR_R_S) w = ROBOT_MIN_ANGULAR_R_S;

    float v_l = (2 * v - w * ROBOT_WHEEL_SEPARATION) / (2 * ROBOT_WHEEL_RADIUS);
    float v_r = (2 * v + w * ROBOT_WHEEL_SEPARATION) / (2 * ROBOT_WHEEL_RADIUS);

    drive(v_l, v_r);
}


