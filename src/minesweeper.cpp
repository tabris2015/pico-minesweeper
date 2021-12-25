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
right_motor2_(pins_.rm2_lpwm, pins_.rm2_rpwm),
arm_(pins_.arm_base_en, pins_.arm_base_pwm, pins_.arm_elbow_en, pins_.arm_elbow_pwm, TOP)
{
    // init metal detector
    adc_init();
    adc_gpio_init(pins_.sensor);
    adc_select_input(get_adc_input(pins_.sensor));

    // init end sensors
    gpio_init(pins_.arm_left_end);
    gpio_init(pins_.arm_right_end);
    gpio_init(pins_.arm_up_end);
    gpio_init(pins_.arm_down_end);

    gpio_set_dir(pins_.arm_left_end, GPIO_IN);
    gpio_set_dir(pins_.arm_right_end, GPIO_IN);
    gpio_set_dir(pins_.arm_up_end, GPIO_IN);
    gpio_set_dir(pins_.arm_down_end, GPIO_IN);

    gpio_pull_down(pins_.arm_left_end);
    gpio_pull_down(pins_.arm_right_end);
    gpio_pull_down(pins_.arm_up_end);
    gpio_pull_down(pins_.arm_down_end);

    // init actuators
    gpio_init(pins_.magnet);
    gpio_init(pins_.alarm);

    gpio_set_dir(pins_.magnet, GPIO_OUT);
    gpio_set_dir(pins_.alarm, GPIO_OUT);

    set_magnet(false);
    set_alarm(false);

    drive(0, 0);
    write_arm(0, 0);
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

void Minesweeper::write_arm(float base, float elbow) {
    // check if sensors are active
    if (gpio_get(pins_.arm_left_end) || gpio_get(pins_.arm_right_end))
        base = 0.0f;

    if ((gpio_get(pins_.arm_up_end) && elbow > 0) ||
        (gpio_get(pins_.arm_up_end) && elbow < 0))
        elbow = 0.0f;

    arm_.write(base, elbow);
}

void Minesweeper::write_commands(ControlCommands commands) {
    // read sensors
    left_sensor_ = gpio_get(pins_.arm_left_end);
    right_sensor_ = gpio_get(pins_.arm_right_end);
    up_sensor_ = gpio_get(pins_.arm_up_end);
    down_sensor_ = gpio_get(pins_.arm_down_end);
    drive_unicycle(commands.linear, commands.angular);
    write_arm(commands.arm_base, commands.arm_elbow);
    set_magnet(commands.magnet);
    set_alarm(commands.alarm);
    if(get_mine()){
        gpio_put(pins_.alarm, true);
    } else {
        gpio_put(pins_.alarm, false);
    }
}

void Minesweeper::set_magnet(bool value) {
    gpio_put(pins_.magnet, value);
}

void Minesweeper::set_alarm(bool value) {
    gpio_put(pins_.alarm, value);
}

void Minesweeper::print_state(void) {
    printf("(%d)[%d %d %d],%.2f,%d,%d,%d,%d", state_.is_mine_detected, mine_t_0, mine_t_1, mine_t_2, state_.sensor_voltage ,left_sensor_, right_sensor_, up_sensor_, down_sensor_);
}

uint Minesweeper::get_adc_input(uint pin) {
    switch (pin) {
        case 26:    return 0;
        case 27:    return 1;
        case 28:    return 2;
        default:    return 0;
    }
}

bool Minesweeper::get_mine() {
    const float factor = 3.3f / (1 << 12);
    uint16_t result = adc_read();
    state_.sensor_voltage = result * factor;
    // remember last 2 measures
    mine_t_2 = mine_t_1;
    mine_t_1 = mine_t_0;
    mine_t_0 = state_.sensor_voltage > 2.45f;

    if(mine_t_2 || mine_t_1 || mine_t_0)
        state_.is_mine_detected = true;
    else if (!mine_t_2 && !mine_t_1 && !mine_t_0)
        state_.is_mine_detected = false;

    return state_.is_mine_detected;
}



