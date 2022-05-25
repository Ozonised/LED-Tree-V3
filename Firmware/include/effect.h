#pragma once

#include <Arduino.h>

enum effect
{
    /* Effects name and their order */
    ALL_LED_OFF = 0,
    MOVING_TRAIN,
    MOVING_TRAIN_REVERSE,
    FADE,
    MOVE_UP,
    MOVE_DOWN,
    SPIN_EACH_LAYER,
    BOTH_MOVING_TRAIN,
    KNIGHT_RIDER,
    BREATHING,
    ALL_LED_ON
};

/* ------------ Fucntion Declarations ------------ */

void allLedsOff();
void ledsOn();
void movingTrain();
void spinEachLayer();
void movingTrainReverse();
void moveUp();
void moveDown();
void knightRider();
void fadeRows();
void breathing();

/* ----------------------------------------------- */
