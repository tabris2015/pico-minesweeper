#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "minesweeper.h"
#include "motor_bts7960.h"
#include "pins.h"

MinesweeperPins pins = {
        M1_LPWM_PIN, M1_RPWM_PIN,
        M2_LPWM_PIN, M2_RPWM_PIN,
        M3_LPWM_PIN, M3_RPWM_PIN,
        M4_LPWM_PIN, M4_RPWM_PIN
};

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    MotorBts7960 motor1(M1_LPWM_PIN, M1_RPWM_PIN);
    Minesweeper robot(pins, true);

    while(true) {
        gpio_put(LED_PIN, 0);
        for(float i = 0.0f; i < 1.0f; i+=0.01f){
            robot.drive(i, i);
            sleep_ms(20);
        }
        for(float i = 1.0f; i > 0.0f; i-=0.01f){
            robot.drive(i, i);
            sleep_ms(20);
        }
        gpio_put(LED_PIN, 1);
        for(float i = 0.0f; i < 1.0f; i+=0.01f){
            robot.drive(-i, -i);
            sleep_ms(20);
        }
        for(float i = 1.0f; i > 0.0f; i-=0.01f){
            robot.drive(-i, -i);
            sleep_ms(20);
        }
    }
}
