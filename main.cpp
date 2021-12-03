#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "minesweeper.h"
#include "dfrobot_dual.h"
#include "serial_parser.h"
#include "pins.h"

MinesweeperPins pins = {
        M1_LPWM_PIN, M1_RPWM_PIN,
        M2_LPWM_PIN, M2_RPWM_PIN,
        M3_LPWM_PIN, M3_RPWM_PIN,
        M4_LPWM_PIN, M4_RPWM_PIN,
        ARM_M1_EN_PIN, ARM_M1_PWM_PIN,
        ARM_M2_EN_PIN, ARM_M2_PWM_PIN
};

Minesweeper robot(pins, true);
float linear_vel;
float angular_vel;
float left_level;
float right_level;
SerialParser parser('/', LED_PIN);
ControlCommands commands;

void setup(){
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

bool timer_callback(repeating_timer * rt){
    robot.drive_unicycle(commands.linear, commands.angular);
    robot.write_arm(0, 0);
    return true;
}
void fail_routine()
{
    while (true)
    {
        gpio_put(LED_PIN, true);
        sleep_ms(50);
        gpio_put(LED_PIN, false);
        sleep_ms(1500);
    }
}

int main() {

    setup();

    repeating_timer_t timer;
    int32_t sample_time_ms = 20;
    if(!add_repeating_timer_ms(sample_time_ms, timer_callback, NULL, &timer)){
        fail_routine();
    }

    printf("Hola bola!\n");
    while(true) {
        commands = parser.parse();
        sleep_ms(1);
    }
}
