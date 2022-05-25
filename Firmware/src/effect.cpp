#include <Arduino.h>
#include "pins-config.h"
#include "effect.h"

static void fade();
/* ------------ Function definitons ------------ */

/* ------------ LED EFFECTS ------------ */

/* Turns all leds OFF*/
void allLedsOff(void)
{
    digitalWrite(R_CLK, LOW);
    for (uint8_t i = 0; i < NO_OF_SHIFT_REGISTER; i++)
    {
        shiftOut(SER, SR_CLK, LSBFIRST, 0xff);
    }
    digitalWrite(R_CLK, HIGH);
}
/* Turns all leds ON */
void ledsOn()
{
    digitalWrite(R_CLK, LOW);

    for (uint8_t i = 0; i < NO_OF_SHIFT_REGISTER; i++)
    {
        shiftOut(SER, SR_CLK, LSBFIRST, 0);
    }
    digitalWrite(R_CLK, HIGH);
}

void movingTrain()
{
    uint32_t dummyVal = 0xffffffff;
    uint8_t i;
    // If i is < the total no. of LEDS and the switch has only been pressed once then increament i
    for (i = 0; i < NO_OF_LED && (sw_press == MOVING_TRAIN || sw_press == BOTH_MOVING_TRAIN); i++)
    {
        bitClear(dummyVal, i);

        digitalWrite(R_CLK, LOW); // R_CLK pin low
        /*
          dummyVal is a 32-bit long variable but shiftout()
          can only shift 8 bits at a time. Therefore, it
          requires 4 steps to shiftout 32 bits(4 bytes).
        */
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 24)); // High byte
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 16)); // Second byte
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 8));  // Third byte
        shiftOut(SER, SR_CLK, MSBFIRST, dummyVal);         // Low byte
        digitalWrite(R_CLK, HIGH);                         // R_CLK pin HIGH to latch the data
        delay(40);
    }

    for (i = 0; i < NO_OF_LED && (sw_press == MOVING_TRAIN || sw_press == BOTH_MOVING_TRAIN); i++)
    {
        bitSet(dummyVal, i);
        digitalWrite(R_CLK, LOW);                          // R_CLK pin low
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 24)); // High byte
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 16)); // Second byte
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 8));  // Third byte
        shiftOut(SER, SR_CLK, MSBFIRST, dummyVal);         // Low byte
        digitalWrite(R_CLK, HIGH);                         // R_CLK pin HIGH to latch the data
        delay(40);
    }
}

void spinEachLayer()
{
    byte spin = 0xff;

    for (uint8_t i = 0; i < 8 && sw_press == SPIN_EACH_LAYER; i++)
    {
        bitClear(spin, i);
        digitalWrite(R_CLK, LOW);              // R_CLK pin low
        shiftOut(SER, SR_CLK, MSBFIRST, spin); // Top layer, turning LEDs ON in CW spin
        shiftOut(SER, SR_CLK, LSBFIRST, spin); // second layer, turning LEDs ON in CCW spin
        shiftOut(SER, SR_CLK, MSBFIRST, spin); // Third layer, turning LEDs ON in CW spin
        shiftOut(SER, SR_CLK, LSBFIRST, spin); // Fourth layer turning LEDs ON in CCW spin
        digitalWrite(R_CLK, HIGH);             // R_CLK pin HIGH to latch the data
        delay(83);
    }

    for (uint8_t i = 8; i > 0 && sw_press == SPIN_EACH_LAYER; i--)
    {
        bitSet(spin, i);
        digitalWrite(R_CLK, LOW);              // R_CLK pin low
        shiftOut(SER, SR_CLK, LSBFIRST, spin); // Top layer, turning LEDs OFF in CW spin
        shiftOut(SER, SR_CLK, MSBFIRST, spin); // second layer, turning LEDs OFF in CCW spin
        shiftOut(SER, SR_CLK, LSBFIRST, spin); // Third layer, turning LEDs OFF in CW spin
        shiftOut(SER, SR_CLK, MSBFIRST, spin); // Fourth layer, turning LEDs OFF in CCW spin
        digitalWrite(R_CLK, HIGH);             // R_CLK pin HIGH to latch the data
        delay(83);
    }
}

/* Turns the LEDs ON and OFF in an order opposite to the movingTrain()  */
void movingTrainReverse()
{
    uint32_t dummyVal = 0xffffffff;
    uint8_t i;
    for (i = 0; i < NO_OF_LED && (sw_press == MOVING_TRAIN_REVERSE || sw_press == BOTH_MOVING_TRAIN); i++)
    {
        bitClear(dummyVal, i);

        digitalWrite(R_CLK, LOW);                          // R_CLK pin low
        shiftOut(SER, SR_CLK, LSBFIRST, dummyVal);         // High byte
        shiftOut(SER, SR_CLK, LSBFIRST, (dummyVal >> 8));  // Second byte
        shiftOut(SER, SR_CLK, LSBFIRST, (dummyVal >> 16)); // Third byte
        shiftOut(SER, SR_CLK, LSBFIRST, (dummyVal >> 24)); // Low byte
        digitalWrite(R_CLK, HIGH);                         // R_CLK pin HIGH to latch the data
        delay(40);
    }

    for (i = 0; i < NO_OF_LED && (sw_press == MOVING_TRAIN_REVERSE || sw_press == BOTH_MOVING_TRAIN); i++)
    {
        bitSet(dummyVal, i);
        digitalWrite(R_CLK, LOW);                          // R_CLK pin low
        shiftOut(SER, SR_CLK, LSBFIRST, dummyVal);         // High byte
        shiftOut(SER, SR_CLK, LSBFIRST, (dummyVal >> 8));  // Second byte
        shiftOut(SER, SR_CLK, LSBFIRST, (dummyVal >> 16)); // Third byte
        shiftOut(SER, SR_CLK, LSBFIRST, (dummyVal >> 24)); // Low byte
        digitalWrite(R_CLK, HIGH);                         // R_CLK pin HIGH to latch the data
        delay(40);
    }
}

void fadeRows()
{
    uint8_t i = 0;

    digitalWrite(R_CLK, LOW);
    /* Lighting up bottom row and second row */
    for (uint8_t j = 0; j < NO_OF_SHIFT_REGISTER && sw_press == FADE; j++)
    {
        i = ~i; // Fliping the value of i
        shiftOut(SER, SR_CLK, LSBFIRST, i);
    }
    digitalWrite(R_CLK, HIGH);
    fade();

    delay(60);

    i = 0xff;
    digitalWrite(R_CLK, LOW);
    /* Turning bottom and second row off while turning on first and third row */
    for (uint8_t j = 0; j < NO_OF_SHIFT_REGISTER && sw_press == FADE; j++)
    {
        i = ~i;
        shiftOut(SER, SR_CLK, LSBFIRST, i);
    }
    digitalWrite(R_CLK, HIGH);
    fade();

    delay(60);

    /* Turning all leds on and then fading them(creating the breathing effect) */
    ledsOn();
    fade();

    delay(60);
}

static void fade()
{
    uint8_t fadeVal;
    /* Increasing brightness */
    for (fadeVal = 0; fadeVal < 200 && (sw_press == FADE || sw_press == BREATHING); fadeVal++)
    {
        OCR1A = fadeVal;
        delay(15);
    }
    /* Decreasing brightness */
    for (fadeVal = 200; fadeVal > 0 && (sw_press == FADE || sw_press == BREATHING); fadeVal--)
    {
        OCR1A = fadeVal;
        delay(15);
    }
}

/*
  Lights up each layer one after another and
  then turns them off one after another starting
  from the bottom layer
*/
void moveUp()
{
    uint8_t i;
    for (i = 0; i < NO_OF_SHIFT_REGISTER && (sw_press == MOVE_UP || sw_press == KNIGHT_RIDER); i++)
    {
        digitalWrite(R_CLK, LOW);
        shiftOut(SER, SR_CLK, LSBFIRST, 0x00);
        digitalWrite(R_CLK, HIGH);
        delay(100);
    }

    for (i = 0; i < NO_OF_SHIFT_REGISTER && (sw_press == MOVE_UP || sw_press == KNIGHT_RIDER); i++)
    {
        digitalWrite(R_CLK, LOW);
        shiftOut(SER, SR_CLK, LSBFIRST, 0xff);
        digitalWrite(R_CLK, HIGH);
        delay(100);
    }
}

/*
  Turns OFF each layer one after another and
  then turns them ON one after another starting
  from the top layer
*/
void moveDown()
{
    uint8_t i;
    unsigned long dummyVal = 0xffffffff;

    for (i = 0; i < NO_OF_SHIFT_REGISTER && (sw_press == MOVE_DOWN || sw_press == KNIGHT_RIDER); i++)
    {
        dummyVal >>= 8;
        digitalWrite(R_CLK, LOW);
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 24)); // High byte
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 16)); // Second byte
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 8));  // Third byte
        shiftOut(SER, SR_CLK, MSBFIRST, dummyVal);         // Low byte
        digitalWrite(R_CLK, HIGH);
        delay(100);
    }
    for (i = 0; i <= NO_OF_SHIFT_REGISTER && (sw_press == MOVE_DOWN || sw_press == KNIGHT_RIDER); i++)
    {
        dummyVal |= (0xffUL << (i * 8));
        digitalWrite(R_CLK, LOW);
        shiftOut(SER, SR_CLK, MSBFIRST, dummyVal);         // Low byte
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 8));  // Third byte
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 16)); // Second byte
        shiftOut(SER, SR_CLK, MSBFIRST, (dummyVal >> 24)); // High byte
        digitalWrite(R_CLK, HIGH);
        delay(100);
    }
}

void knightRider()
{
    moveUp();
    delay(150);
    moveDown();
    delay(150);
}

/* Turning all leds on and then fading them(creating the breathing effect) */
void breathing(void)
{
    ledsOn();
    fade();
}
