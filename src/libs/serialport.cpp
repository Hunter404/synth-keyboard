#include "Arduino.h"

#define SERIAL_PORT_BAUD 115200
#define SERIAL_PORT_BUFFER_SIZE 96

namespace Synth {
    class SerialPortInterface {
        private:
        public:
            static void start() {
                Serial.begin(SERIAL_PORT_BAUD);
            }

            static void stop() {
                Serial.end();
            }

            static void getData() {
                static char spBuffer[96];
                static int spIndex = 0;

                while (Serial.available() > 0)
                {
                    if (spIndex < 80) {
                        char c = Serial.read();
                        spBuffer[spIndex] = c;
                    
                        spIndex++;
                    } else {
                        Serial.println("OVERFLOW");
                        spIndex = 0;

                        for (int i = 0; i < SERIAL_PORT_BUFFER_SIZE; i++) {
                        spBuffer[i] = '\0';
                        }
                    }
                }

                String serialData = String(spBuffer);
                int newLineIndex = serialData.indexOf("\r\n");
                if (newLineIndex > 0) {
                    String commandString = serialData.substring(0, newLineIndex);

                    // CLEAR BUFFER
                    spIndex -= newLineIndex + 2;
                    for (int i = 0; i < SERIAL_PORT_BUFFER_SIZE; i++) {
                        if (i < newLineIndex) {
                        spBuffer[i] = spBuffer[i + newLineIndex];
                        } else {
                        spBuffer[i] = '\0';
                        }
                    }

                    int commandIndex = commandString.indexOf(' ');
                    String c;
                    if (commandIndex == -1) {
                        c = commandString;
                    } else {
                        c = commandString.substring(0, commandIndex);
                    }

                    Serial.println(c);

                    // VERSION
                    if (c == "Q") {
                        Serial.println("SYNTH VERSION 1.1 BY FREDRIK LARSSON");
                    } else if (c == "HelloWorld") {
                        Serial.println("Hello to you to :)");
                    } else {
                        Serial.println("Incorrect command");
                    }

                    Serial.println("OK");
                }
            }
    };
};