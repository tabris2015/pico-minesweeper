#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "motor_bts7960.h"
#include "pins.h"

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    MotorBts7960 motor1(M1_LPWM_PIN, M1_RPWM_PIN);
    while(true) {
        gpio_put(LED_PIN, 0);
        for(float i = 0.0f; i < 1.0f; i+=0.01f){
            motor1.write(i);
            sleep_ms(20);
        }
        for(float i = 1.0f; i > 0.0f; i-=0.01f){
            motor1.write(i);
            sleep_ms(20);
        }
        gpio_put(LED_PIN, 1);
        for(float i = 0.0f; i < 1.0f; i+=0.01f){
            motor1.write(-i);
            sleep_ms(20);
        }
        for(float i = 1.0f; i > 0.0f; i-=0.01f){
            motor1.write(-i);
            sleep_ms(20);
        }
	}
}
