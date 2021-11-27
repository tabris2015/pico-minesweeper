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
    float val1;
    float val2;
};


class SerialParser {
public:
    SerialParser(const char end_token, uint gpio_pin);
    ControlCommands parse();
    void print_state();
    void print_commands();

private:
    int ch_;
    int ch_idx_;
    float value1_;
    float value2_;
    float value3_;
    const char end_token_;
    char * ch_ptr_;
    char * ch_ptr2_;
    char * ch_ptr3_;
    uint gpio_pin_;
    ControlCommands commands_;
    char in_buffer_[100];
};


#endif //PICO_MINESWEEPER_SERIAL_PARSER_H
