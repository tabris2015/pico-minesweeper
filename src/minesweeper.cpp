//
// Created by pepe on 25/11/21.
//

#include "minesweeper.h"

Minesweeper::Minesweeper(MinesweeperPins pins, bool has_four_motors)
:
pins_(pins),
left_motor1_(pins_.lm1_lpwm, pins_.lm1_rpwm),
right_motor1_(pins_.rm1_lpwm, pins_.rm1_rpwm),
left_motor2_(pins_.lm2_lpwm, pins_.lm2_rpwm),
right_motor2_(pins_.rm2_lpwm, pins_.rm2_rpwm)
{
    drive(0, 0);
}

void Minesweeper::write_motor(MotorId motor_id, float duty_cycle) {
    switch (motor_id) {
        case MotorId::m1:
            left_motor1_.write(duty_cycle);
            break;
        case MotorId::m2:
            right_motor1_.write(duty_cycle);
            break;
        case MotorId::m3:
            left_motor2_.write(duty_cycle);
            break;
        case MotorId::m4:
            right_motor2_.write(duty_cycle);
            break;
        default:
            break;
    }
}

void Minesweeper::drive(float left, float right) {
    left_motor1_.write(left);
    right_motor1_.write(right);
    left_motor2_.write(left);
    right_motor2_.write(right);
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


