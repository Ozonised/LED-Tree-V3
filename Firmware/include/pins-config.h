#pragma once

#include <Arduino.h>

/* Connection to shift register */
#define OE PB1
#define SER 3
#define SR_CLK 4
#define R_CLK 6

/* Connection to switches and potentiometer */
#define POT_PIN PC0    // For brightness control
#define SWITCH_PIN PD2 // For toggling effects

#define NO_OF_LED 32
#define NO_OF_SHIFT_REGISTER 4

extern volatile uint8_t sw_press; // stores the no. of switch presses