#ifndef _IO_TEST
#define _IO_TEST

#include "Arduino.h"
#include "io/io.h"
#include "libs/multiplexer.cpp"

namespace Synth
{
    class IOTest
    {
        private:
        public:
            static void test()
            {
                // Test slide pots
                for (int i = 1; i <= 9; i++)
                {
                    while (true)
                    {
                        int input = IO::readSlidePot(i);
                        input = (input % 32) ? input / 32 + 1 : input / 32;

                        for (int j = 0; j < 32; j++)
                        {
                            if (j < input)
                                IO::trellis.setPixelColor(j, IO::wheel(map(j, 0, NEOTRELLIS_X_DIM*NEOTRELLIS_Y_DIM, 0, 255)));
                            else
                                IO::trellis.setPixelColor(j, 0);
                        }

                        IO::trellis.show();

                        delay(20);

                        if (input >= 31) break;
                    }
                }

                // Test pots
                for (int i = 1; i <= 13; i++)
                {
                    while (true)
                    {
                        int input = IO::readPot(i);
                        input = (input % 32) ? input / 32 + 1 : input / 32;

                        for (int j = 0; j < 32; j++)
                        {
                            if (j < input)
                                IO::trellis.setPixelColor(j, IO::wheel(j));
                            else
                                IO::trellis.setPixelColor(j, 0);
                        }

                        IO::trellis.show();

                        delay(20);

                        if (input >= 31) break;
                    }
                }

                for (int i = 1; i <= 3; i++)
                {
                    while (true)
                    {
                        int input = IO::readButton(i) * 32;
                        for (int j = 0; j < 32; j++)
                        {
                            if (j < input)
                                IO::trellis.setPixelColor(j, IO::wheel(j));
                            else
                                IO::trellis.setPixelColor(j, 0);
                        }

                        IO::trellis.show();

                        delay(20);

                        if (input >= 31) break;
                    }
                }

                Serial.print("Pushbutton 1: ");
                Serial.println(IO::readButton(1));
                Serial.print("Pushbutton 2: ");
                Serial.println(IO::readButton(2));
                Serial.print("Pushbutton 3: ");
                Serial.println(IO::readButton(3));

                Serial.print("Slidepot 1: ");
                Serial.println(IO::readSlidePot(1));
                Serial.print("Slidepot 2: ");
                Serial.println(IO::readSlidePot(2));
                Serial.print("Slidepot 3: ");
                Serial.println(IO::readSlidePot(3));
                Serial.print("Slidepot 4: ");
                Serial.println(IO::readSlidePot(4));
                Serial.print("Slidepot 5: ");
                Serial.println(IO::readSlidePot(5));
                Serial.print("Slidepot 6: ");
                Serial.println(IO::readSlidePot(6));
                Serial.print("Slidepot 7: ");
                Serial.println(IO::readSlidePot(7));
                Serial.print("Slidepot 8: ");
                Serial.println(IO::readSlidePot(8));
                Serial.print("Slidepot 9: ");
                Serial.println(IO::readSlidePot(9));

                Serial.print("Pot 1: ");
                Serial.println(IO::readPot(1));
                Serial.print("Pot 2: ");
                Serial.println(IO::readPot(2));
                Serial.print("Pot 3: ");
                Serial.println(IO::readPot(3));
                Serial.print("Pot 4: ");
                Serial.println(IO::readPot(4));
                Serial.print("Pot 5: ");
                Serial.println(IO::readPot(5));
                Serial.print("Pot 6: ");
                Serial.println(IO::readPot(6));
                Serial.print("Pot 7: ");
                Serial.println(IO::readPot(7));
                Serial.print("Pot 8: ");
                Serial.println(IO::readPot(8));
                Serial.print("Pot 9: ");
                Serial.println(IO::readPot(9));
                Serial.print("Pot 10: ");
                Serial.println(IO::readPot(10));
                Serial.print("Pot 11: ");
                Serial.println(IO::readPot(11));
                Serial.print("Pot 12: ");
                Serial.println(IO::readPot(12));
                Serial.print("Pot 13: ");
                Serial.println(IO::readPot(13));
            }
    };
};

#endif