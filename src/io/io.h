#ifndef _IO_H
#define _IO_H

#include "Arduino.h"
#include "Adafruit_NeoTrellis.h"
#include "libs/multiplexer.cpp"
#include <stdexcept>

// Buttons
#define PB1 28
#define PB2 27
#define PB3 26

// Pots
#define POT1  10
#define POT2  11
#define POT3  4
#define POT4  5
#define POT5  6
#define POT6  7
#define POT7  12
#define POT8  13
#define POT9  14
#define POT10 15
#define POT11 9
#define POT12 8
#define POT13 3

// Slidepots
#define SLIDE_POT1 0
#define SLIDE_POT2 1
#define SLIDE_POT3 35
#define SLIDE_POT4 36
#define SLIDE_POT5 31
#define SLIDE_POT6 32
#define SLIDE_POT7 33
#define SLIDE_POT8 34
#define SLIDE_POT9 2

// NeoTrellis Pin
#define NEOTRELLIS_INT_PIN 47
#define NEOTRELLIS_X_DIM 8
#define NEOTRELLIS_Y_DIM 4

namespace Synth
{
    class IO
    {
        private:
            static boolean initialized;
            static Adafruit_NeoTrellis t_array[NEOTRELLIS_Y_DIM / 4][NEOTRELLIS_X_DIM / 4];
        public:
            static Adafruit_MultiTrellis trellis;
            static uint32_t wheel(byte wheelPos);
            static void setup();
            static void update();
            static bool readButton(unsigned char index);
            static float readSlidePot(unsigned char index);
            static float readPot(unsigned char index);
    };
};

#endif