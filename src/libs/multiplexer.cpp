#include "Arduino.h"

// MUX: Pins
#define MUX_S0 3
#define MUX_S1 4
#define MUX_S2 5
#define MUX_S3 6
#define MUX_SIG 28

namespace Synth {
    class Multiplexer {
        public: 
            int readMux(int channel){
                int controlPin[] = {
                    MUX_S0,
                    MUX_S1,
                    MUX_S2,
                    MUX_S3
                };

                int muxChannel[16][4]={
                    {0,0,0,0}, //channel 0
                    {1,0,0,0}, //channel 1
                    {0,1,0,0}, //channel 2
                    {1,1,0,0}, //channel 3
                    {0,0,1,0}, //channel 4
                    {1,0,1,0}, //channel 5
                    {0,1,1,0}, //channel 6
                    {1,1,1,0}, //channel 7
                    {0,0,0,1}, //channel 8
                    {1,0,0,1}, //channel 9
                    {0,1,0,1}, //channel 10
                    {1,1,0,1}, //channel 11
                    {0,0,1,1}, //channel 12
                    {1,0,1,1}, //channel 13
                    {0,1,1,1}, //channel 14
                    {1,1,1,1}  //channel 15
                };

                for(int i = 0; i < 4; i ++){
                    digitalWrite(controlPin[i], muxChannel[channel][i]);
                }

                int val;
                val = analogRead(MUX_SIG);

                return val;
            }
    };
};
