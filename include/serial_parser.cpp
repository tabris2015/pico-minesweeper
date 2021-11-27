//
// Created by pepe on 27/11/21.
//

#include "serial_parser.h"

SerialParser::SerialParser(const char end_token, uint gpio_pin)
:end_token_(end_token), gpio_pin_(gpio_pin) {

}

ControlCommands SerialParser::parse() {
    ch_ = getchar_timeout_us(0);
    while (ch_ != PICO_ERROR_TIMEOUT){
        gpio_put(gpio_pin_, true);
//        putchar(ch_);   // echo
        in_buffer_[ch_idx_++] = ch_;
//        printf("\nbuffer: %s\n", in_buffer_);
        if(ch_ == end_token_){
            in_buffer_[ch_idx_] = 0;
//            printf("\nreceived: %s\n", in_buffer_);
            ch_idx_ = 0;
            value1_ = strtof(in_buffer_, &ch_ptr_);
            value2_ = strtof(ch_ptr_ + 1, &ch_ptr2_);
            print_commands();
            break;
        }
        ch_ = getchar_timeout_us(0);
    }
    gpio_put(gpio_pin_, false);

    return commands_;
}

void SerialParser::print_commands() {
    printf("%.3f, %.3f\n", value1_, value2_);
}
