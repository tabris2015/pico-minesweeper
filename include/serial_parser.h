//
// Created by pepe on 27/11/21.
//

#ifndef PICO_MINESWEEPER_SERIAL_PARSER_H
#define PICO_MINESWEEPER_SERIAL_PARSER_H
#include "stdio.h"
#include "pico/stdlib.h"
#include "cstdlib"
#include "pico/time.h"

struct ControlCommands{
    float linear;
    float angular;
    float arm_base;
    float arm_elbow;
    bool magnet;
    bool alarm;
};


class SerialParser {
public:
    SerialParser(const char end_token, uint gpio_pin);
    bool parse(ControlCommands& commands);
    void print_state();
    void print_commands();

private:
    int ch_;
    int ch_idx_;
    const char end_token_;
    char * ch_ptr_;
    char * ch_ptr2_;
    uint gpio_pin_;
    ControlCommands commands_;
    char in_buffer_[100];
};


#endif //PICO_MINESWEEPER_SERIAL_PARSER_H
