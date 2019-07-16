#ifndef _IO_C
#define _IO_C

#include "io.h"

namespace Synth {
    uint32_t IO::wheel(unsigned char wheelPos) {
        if(wheelPos < 85) {
            return seesaw_NeoPixel::Color(wheelPos * 3, 255 - wheelPos * 3, 0);
        }
        else if(wheelPos < 170)
        {
            wheelPos -= 85;
            return seesaw_NeoPixel::Color(255 - wheelPos * 3, 0, wheelPos * 3);
        }
        else
        {
            wheelPos -= 170;
            return seesaw_NeoPixel::Color(0, wheelPos * 3, 255 - wheelPos * 3);
        }
    }

    void IO::setup()
    {
        Multiplexer::setup();

        // Buttons
        pinMode(PB1, INPUT_PULLUP);
        pinMode(PB2, INPUT_PULLUP);
        pinMode(PB3, INPUT_PULLUP);

        // Keypad
        pinMode(NEOTRELLIS_INT_PIN, INPUT);

        while (!trellis.begin())
        {
            Serial.println("failed to begin trellis");
        }

        /* the array can be addressed as x,y or with the key number */
        for(int i = 0; i < NEOTRELLIS_Y_DIM * NEOTRELLIS_X_DIM; i++)
        {
            trellis.setPixelColor(i, wheel(map(i, 0, NEOTRELLIS_X_DIM * NEOTRELLIS_Y_DIM, 0, 255))); //addressed with keynum
            trellis.show();
            delay(10);
        }

        for(int y = 0; y < NEOTRELLIS_Y_DIM; y++)
        {
            for(int x = 0; x < NEOTRELLIS_X_DIM; x++)
            {
                //activate rising and falling edges on all keys
                trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_RISING, true);
                trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_FALLING, true);
                trellis.setPixelColor(x, y, 0x000000); //addressed with x,y
                trellis.show(); //show all LEDs
                delay(10);
            }
        }

        initialized = true;
    }

    void IO::update()
    {
        if (!initialized) return;

        trellis.read();
    }

    bool IO::readButton(unsigned char index)
    {
        switch (index)
        {
            case 1:
                return digitalRead(PB1) == 0;
            case 2:
                return digitalRead(PB2) == 0;
            case 3:
                return digitalRead(PB3) == 0;
            default:
                Serial.print("Error: readButton ");
                Serial.print(index);
                Serial.print(" out of range exception");
                return false;
        }
    }

    float IO::readSlidePot(unsigned char index)
    {
        switch (index)
        {
            case 1:
                return (float) Multiplexer::readMux(SLIDE_POT1) / 1023.0;
            case 2:
                return (float) Multiplexer::readMux(SLIDE_POT2) / 1023.0;
            case 3:
                return (float) analogRead(SLIDE_POT3) / 1023.0;
            case 4:
                return (float) analogRead(SLIDE_POT4) / 1023.0;
            case 5:
                return (float) analogRead(SLIDE_POT5) / 1023.0;
            case 6:
                return (float) analogRead(SLIDE_POT6) / 1023.0;
            case 7:
                return (float) analogRead(SLIDE_POT7) / 1023.0;
            case 8:
                return (float) analogRead(SLIDE_POT8) / 1023.0;
            case 9:
                return (float) Multiplexer::readMux(SLIDE_POT9) / 1023.0;
            default:
                Serial.print("Error: readSlidePot ");
                Serial.print(index);
                Serial.print(" out of range exception");
                return 0;
        }
    }

    float IO::readPot(unsigned char index)
    {
        switch (index)
        {
            case 1:
                return (float) Multiplexer::readMux(POT1) / 1023.0;
            case 2:
                return (float) Multiplexer::readMux(POT2) / 1023.0;
            case 3:
                return (float) Multiplexer::readMux(POT3) / 1023.0;
            case 4:
                return (float) Multiplexer::readMux(POT4) / 1023.0;
            case 5:
                return (float) Multiplexer::readMux(POT5) / 1023.0;
            case 6:
                return (float) Multiplexer::readMux(POT6) / 1023.0;
            case 7:
                return (float) Multiplexer::readMux(POT7) / 1023.0;
            case 8:
                return (float) Multiplexer::readMux(POT8) / 1023.0;
            case 9:
                return (float) Multiplexer::readMux(POT9) / 1023.0;
            case 10:
                return (float) Multiplexer::readMux(POT10) / 1023.0;
            case 11:
                return (float) Multiplexer::readMux(POT11) / 1023.0;
            case 12:
                return (float) Multiplexer::readMux(POT12) / 1023.0;
            case 13:
                return (float) Multiplexer::readMux(POT13) / 1023.0;
            default:
                Serial.print("Error: readPot ");
                Serial.print(index);
                Serial.print(" out of range exception");
                return 0;
        }
    }

    Adafruit_NeoTrellis IO::t_array[NEOTRELLIS_Y_DIM / 4][NEOTRELLIS_X_DIM / 4] = { { *new Adafruit_NeoTrellis(0x2E), *new Adafruit_NeoTrellis(0x2F) } };
    Adafruit_MultiTrellis IO::trellis = *new Adafruit_MultiTrellis((Adafruit_NeoTrellis *)IO::t_array, NEOTRELLIS_Y_DIM / 4, NEOTRELLIS_X_DIM / 4);
    boolean IO::initialized = false;
}

#endif