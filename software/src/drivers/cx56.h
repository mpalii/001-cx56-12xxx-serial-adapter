#ifndef CX56_H_
#define CX56_H_

#include "gpio.h"
#include <stdint.h>

#if (!defined(COMMON_ANODE_MODE) && !defined(COMMON_CATHODE_MODE))
# error "Connection mode for CX56 is not specified!"
#endif

#ifdef COMMON_CATHODE_MODE
# define _SEGMENT_ENABLE(GPIO) GPIO_HIGH(GPIO)
# define _SEGMENT_DISABLE(GPIO) GPIO_LOW(GPIO)
# define _DIGIT_ENABLE(GPIO) GPIO_LOW(GPIO)
# define _DIGIT_DISABLE(GPIO) GPIO_HIGH(GPIO)
#endif

#ifdef COMMON_ANODE_MODE
# define _SEGMENT_ENABLE(GPIO) GPIO_LOW(GPIO)
# define _SEGMENT_DISABLE(GPIO) GPIO_HIGH(GPIO)
# define _DIGIT_ENABLE(GPIO) GPIO_HIGH(GPIO)
# define _DIGIT_DISABLE(GPIO) GPIO_LOW(GPIO)
#endif

void render(uint16_t number);

#endif /* CX56_H_ */