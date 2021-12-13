//
// Created by pepe on 25/11/21.
//

#ifndef PICO_MINESWEEPER_MINESWEEPER_H
#define PICO_MINESWEEPER_MINESWEEPER_H

#include "pico/stdlib.h"
#include "motor_bts7960.h"
#include "dfrobot_dual.h"
#include "serial_parser.h"


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
    uint rm1_lpwm;
    uint rm1_rpwm;
    uint rm2_lpwm;
    uint rm2_rpwm;
    uint lm2_lpwm;
    uint lm2_rpwm;
    uint lm1_lpwm;
    uint lm1_rpwm;
    uint arm_base_en;
    uint arm_base_pwm;
    uint arm_elbow_en;
    uint arm_elbow_pwm;
    uint arm_left_end;
    uint arm_right_end;
    uint arm_up_end;
    uint arm_down_end;
    uint magnet;
    uint alarm;
};

struct MinesweeperState{
    bool is_mine_detected;
};

class Minesweeper {
public:
    Minesweeper(MinesweeperPins pins, bool has_four_motors);
    void write_motor(MotorId motor_id, float duty_cycle);
    void drive(float left, float right);
    void drive_unicycle(float v, float w);
    void write_arm(float base, float elbow);
    void write_commands(ControlCommands commands);
    void set_magnet(bool value);
    void set_alarm(bool value);
    void print_state(void);
private:
    MinesweeperPins pins_;
    MotorBts7960 left_motor1_;
    MotorBts7960 right_motor1_;
    MotorBts7960 left_motor2_;
    MotorBts7960 right_motor2_;
    DfRobotDual arm_;
    bool has_mine_;
    bool left_sensor_;
    bool right_sensor_;
    bool up_sensor_;
    bool down_sensor_;

};


#endif //PICO_MINESWEEPER_MINESWEEPER_H
