/**
 * @author Maksym Palii
 * @brief Seven-segment display
 * @version 1.0
*/

#define BASE 10
#define DIGIT_WITH_DECIMAL_POINT DIGIT_3

#include "cx56.h"

#define DIGIT_1 ~_BV(0)
#define DIGIT_2 ~_BV(1)
#define DIGIT_3 ~_BV(2)
#define DIGIT_4 ~_BV(3)

// Digits placed from lower to higher
const uint8_t DIGIT_MASKS[] = { DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4 };

const uint8_t NUMBERS[] = {
    0b00111111, 0b00000110, 0b01011011,	0b01001111,	// 0, 1, 2, 3
    0b01100110, 0b01101101,	0b01111101,	0b00000111,	// 4, 5, 6, 7
    0b01111111, 0b01101111,	0b01110111,	0b01111100,	// 8, 9, A, B
    0b00111001,	0b01011110,	0b01111001, 0b01110001	// C, D, E, F
};

uint8_t current_digit = 0;

void render(uint16_t number) 
{

    if (current_digit >= sizeof(DIGIT_MASKS)) 
	{
		current_digit = 0;
	}

	for (int i = 0; i < current_digit; i++)
	{
		number /= BASE;
	}

    #ifdef NO_LEADING_ZEROS_MODE
    if (current_digit > 1 && number == 0) {
        current_digit++;
        return;
    }
    #endif
	
	number %= BASE;

    // Shift digit related byte
    uint8_t digit_byte = DIGIT_MASKS[current_digit];
    for (int8_t i = 7; i >= 0; i--)
    {
        GPIO_LOW(SRCLK);

        if (digit_byte & (1 << i))
        {
            GPIO_HIGH(SER);
        }
        else
        {
            GPIO_LOW(SER);
        }

        GPIO_HIGH(SRCLK);
    }

    // Shift number related byte
    uint8_t mapped_number = NUMBERS[number];

    if (current_digit == 1) 
    {
        mapped_number |= 1 << 7;
    }

    for (int8_t i = 7; i >= 0; i--)
    {
        GPIO_LOW(SRCLK);

        if (mapped_number & (1 << i))
        {
            GPIO_HIGH(SER);
        }
        else
        {
            GPIO_LOW(SER);
        }

        GPIO_HIGH(SRCLK);
    }

    GPIO_LOW(SRCLK);

    GPIO_HIGH(RCLK);
    GPIO_LOW(RCLK);

    current_digit++;
}
