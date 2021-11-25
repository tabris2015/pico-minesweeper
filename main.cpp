#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "motor_bts7960.h"
#include "pins.h"

int main() {
	stdio_init_all();
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
    MotorBts7960 motor1(M1_LPWM_PIN, M1_RPWM_PIN);
	while(1) {
		gpio_put(LED_PIN, 0);
        motor1.write(-0.7);
		sleep_ms(1000);
        gpio_put(LED_PIN, 1);
        motor1.write(-0.2);
        sleep_ms(1000);
	}
}
