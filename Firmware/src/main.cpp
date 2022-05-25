#include <Arduino.h>
#include "pins-config.h"
#include "effect.h"

volatile uint8_t sw_press = 0;

void setup()
{
  /* ---- Setting the respectives as OUTPUT ---- */
  DDRD |= _BV(SER) | _BV(SR_CLK) | _BV(R_CLK);
  // PORTD |= _BV(PD5);
  cli(); // Disable global interrupts

  /* - Enabling External Interrupt on PD2(INT0) - */

  /* ------ MCUCR - MCU Control Register ------- */

  MCUCR |= _BV(ISC01) | _BV(ISC00); // Interrupt on rising edge

  /*  GICR - General Interrupt Control Register  */

  GICR |= _BV(INT0); // External Interrupt Request 0 Enable

  /* ------------------------------------------ */

  /* ------------- Initializing ADC ------------- */

  /* ADMUX - ADC Multiplexer Selection Register */

  ADMUX |= _BV(REFS0); // AVCC with external capacitor at AREF pin
  ADMUX |= _BV(ADLAR); // ADC Left Adjust Result(8 -bit mode)

  /*
    Bits 3 - 0 in ADMUX select which analog pins to use.
    Since we want to use analog pin 0(ADC0/PC0), ADMUX
    bits 3-0 must be cleared to 0, which they already are.
  */

  /*  ADCSRA - ADC Control and Status Register A  */

  ADCSRA |= _BV(ADEN); // Enable ADC
  ADCSRA |= _BV(ADFR); // ADC Free Running mode(continuously samples)
  ADCSRA |= _BV(ADSC); // Start conversion
  /* -------------------------------------------- */

  /* ------------ Initializing Timer1 ------------ */

  /* TCCR1A - Timer/Counter 1 Control Register A */
  /* TCCR1B - Timer/Counter 1 Control Register B */

  /*
    Since the OE pin is active LOW,
    the PWM signal must be inverted.
  */
  TCCR1A |= _BV(COM1A0) | _BV(COM1A1); // Inverting Fast PWM Mode

  /* Enabling 8-bit Fast PWM Mode */
  TCCR1A |= _BV(WGM10);
  TCCR1B |= _BV(WGM12);

  // Selecting clock prescaler of 8,
  // PWM frequency = 3,906(approx)
  TCCR1B |= _BV(CS11);

  /* TIMSK - Timer/Counter Interrupt Mask Register */

  TIMSK |= _BV(OCIE1A); // Output Compare A Match Interrupt Enable

  /* --------------------------------------------- */
  DDRB |= (1 << OE);
  sei(); // enable global interrupts
}

void loop()
{

  if (sw_press == FADE || sw_press == BREATHING)
  {
    /*
      For fade and breathing effect, the brightness of the LEDs must be controlled via software.
      To do so, we need to manaully write to OCR1A but the value of OCR1A is updated
      to the ADC result in the Output Compare A Match Interrupt vector. By disabling
      Output Compare A Match Interrupt, OCR1A is no longer updated to the ADC result
      and we can now manually write a value to OCR1A.
    */

    /* TIMSK - Timer/Counter Interrupt Mask Register */
    TIMSK &= ~_BV(OCIE1A); // Disabling Output Compare A Match Interrupt
  }
  else
  {
    TIMSK |= _BV(OCIE1A); // Enabling Output Compare A Match Interrupt
  }

  switch (sw_press)
  {
  case ALL_LED_OFF:
    allLedsOff();
    break;

  case MOVING_TRAIN:
    movingTrain();
    break;

  case MOVING_TRAIN_REVERSE:
    movingTrainReverse();
    break;

  case BOTH_MOVING_TRAIN:
    movingTrain();
    delay(125);
    movingTrainReverse();
    delay(125);
    break;

  case SPIN_EACH_LAYER:
    spinEachLayer();
    break;

  case MOVE_UP:
    moveUp();
    break;

  case MOVE_DOWN:
    moveDown();
    break;

  case KNIGHT_RIDER:
    knightRider();
    break;

  case FADE:
    fadeRows();
    break;

  case BREATHING:
    breathing();
    break;

  case ALL_LED_ON:
    ledsOn();
    break;

  default:
    sw_press = 0;
    break;
  }
}

/* ------ Interrupt service routine ------ */

/* Interrupt handler for SWITCH_PIN */
ISR(INT0_vect)
{
  ++sw_press; // Increment the switch press count
}

ISR(TIMER1_COMPA_vect)
{
  OCR1A = ADCH; // Reading ADC result
}
