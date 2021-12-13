//
// Created by pepe on 27/11/21.
//

#include "serial_parser.h"

SerialParser::SerialParser(const char end_token, uint gpio_pin)
:end_token_(end_token), gpio_pin_(gpio_pin) {

}

// Command linear, angular, arm_base, arm_elbow, magnet, alarm /
bool SerialParser::parse(ControlCommands& commands) {
    ch_ = getchar_timeout_us(0);
    while (ch_ != PICO_ERROR_TIMEOUT){
        gpio_put(gpio_pin_, true);
        in_buffer_[ch_idx_++] = ch_;
        if(ch_ == end_token_){
            in_buffer_[ch_idx_] = 0;
            ch_idx_ = 0;
            commands.linear = strtof(in_buffer_, &ch_ptr_);
            commands.angular = strtof(ch_ptr_ + 1, &ch_ptr2_);
            commands.arm_base = strtof(ch_ptr2_ + 1, &ch_ptr_);
            commands.arm_elbow = strtof(ch_ptr_ + 1, &ch_ptr2_);
            commands.magnet = strtol(ch_ptr2_ + 1, &ch_ptr_, 10);
            commands.alarm = strtol(ch_ptr_ + 1, &ch_ptr2_, 10);
//            print_commands();
            gpio_put(gpio_pin_, false);
            return true;
        }
        ch_ = getchar_timeout_us(0);
    }
    gpio_put(gpio_pin_, false);

    return false;
}

void SerialParser::print_commands() {
    printf(
            "parsed: [%f] [%f] [%f] [%f] [%d] [%d]\n",
            commands_.linear,
            commands_.angular,
            commands_.arm_base,
            commands_.arm_elbow,
            commands_.magnet,
            commands_.alarm
            );

}
