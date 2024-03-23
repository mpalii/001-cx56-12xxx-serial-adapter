/**
 * @author Maksym Palii
 * @brief GPIO driver for ATmega328P
 * @version 1.0
 * 
 * Inspired by Niklas Nilsson 
 * @link https://github.com/niklasab
 * @link https://www.artfulbytes.com
 * @link https://www.youtube.com/@artfulbytes
*/

#include "gpio.h"

void gpio_init(void)
{
    GPIO_SET_OUTPUT(SER);
    GPIO_SET_OUTPUT(RCLK);
    GPIO_SET_OUTPUT(SRCLK);
}
