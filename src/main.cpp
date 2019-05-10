#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioOutputI2S           i2s;           //xy=1768.6666564941406,637.9999809265137
AudioControlSGTL5000     codec;     //xy=1494.6666564941406,448.9999809265137
AudioSynthWaveformDc     dc1;            //xy=172.5,573.75
AudioSynthWaveform       lfo;            //xy=226.66665649414062,665.9999809265137
AudioMixer4              mixer1;         //xy=361.25000381469727,536.2500076293945
AudioSynthWaveform       channel1A;      //xy=450.6666564941406,269.9999809265137
AudioSynthWaveform       channel1B;      //xy=450.6666564941406,316.9999809265137
AudioSynthNoiseWhite     channel1C;      //xy=450.6666564941406,362.9999809265137
AudioAnalyzePeak         peak1;          //xy=530,478.75
AudioMixer4              channel1MixerA; //xy=647.6666564941406,289.9999809265137
AudioSynthWaveformDc     channel1Env;    //xy=650.6666564941406,355.9999809265137
AudioSynthWaveformDc     channel1EnvFilter; //xy=664.6666564941406,418.9999809265137
AudioMixer4              channel1MixerB; //xy=861.8484344482422,438.09086990356445
AudioEffectMultiply      channel1Combine; //xy=864.6666564941406,273.9999809265137
AudioFilterStateVariable channel1FilterA; //xy=1045.6666564941406,280.9999809265137
AudioMixer4              childMixer1A;   //xy=1254.6666564941406,530.9999809265137
AudioEffectDelay         audioDelay1C1;  //xy=1470.6666564941406,857.9999809265137
AudioFilterStateVariable audioFilter1C2; //xy=1472.6666564941406,734.9999809265137
AudioMixer4              masterMixer;    //xy=1477.6666564941406,635.9999809265137
AudioConnection          patchCord1(dc1, 0, mixer1, 0);
AudioConnection          patchCord2(lfo, 0, channel1MixerB, 1);
AudioConnection          patchCord3(lfo, 0, mixer1, 1);
AudioConnection          patchCord4(mixer1, peak1);
AudioConnection          patchCord5(channel1A, 0, channel1MixerA, 0);
AudioConnection          patchCord6(channel1B, 0, channel1MixerA, 1);
AudioConnection          patchCord7(channel1C, 0, channel1MixerA, 2);
AudioConnection          patchCord8(channel1MixerA, 0, channel1Combine, 0);
AudioConnection          patchCord9(channel1Env, 0, channel1Combine, 1);
AudioConnection          patchCord10(channel1EnvFilter, 0, channel1MixerB, 0);
AudioConnection          patchCord11(channel1MixerB, 0, channel1FilterA, 1);
AudioConnection          patchCord12(channel1Combine, 0, channel1FilterA, 0);
AudioConnection          patchCord13(channel1FilterA, 0, childMixer1A, 0);
AudioConnection          patchCord14(childMixer1A, 0, masterMixer, 0);
AudioConnection          patchCord15(audioDelay1C1, 0, audioFilter1C2, 0);
AudioConnection          patchCord16(audioFilter1C2, 0, masterMixer, 3);
AudioConnection          patchCord17(masterMixer, audioDelay1C1);
AudioConnection          patchCord18(masterMixer, 0, i2s, 0);
AudioConnection          patchCord19(masterMixer, 0, i2s, 1);
// GUItool: end automatically generated code

#define SET_DEFAULT_GAIN(channelMixer) for(int i = 0; i < 4; i++) channelMixer.gain(i, 0.25)

#include "Arduino.h"

#include "libs/serialport.cpp"
#include "libs/multiplexer.cpp"

using namespace Synth;

float noteFreq[7][8] = {
  //5       1       6      2      7      3      8     4  
  {329.63,220.00,369.99,246.94,415.30,277.18,440.00,293.66},
  {369.99,246.94,415.30,277.18,466.16,311.13,493.88,329.63},
  {392.00,261.63,440.00,293.66,493.88,329.63,523.25,349.23},
  {440.00,293.66,493.88,329.63,554.37,369.99,587.33,392.00},
  {493.88,329.63,554.37,369.99,622.25,415.30,659.25,440.00},
  {523.25,349.23,587.33,392.00,659.25,440.00,698.46,466.16},
  {587.33,392.00,659.25,440.00,739.99,493.88,783.99,523.25},
};

void setup() {

    SerialPortInterface::start();

    AudioMemory(160);

    AudioNoInterrupts();

    codec.enable();
    codec.volume(1);

    SET_DEFAULT_GAIN(channel1MixerA);

    channel1A.begin(0.3, 440, WAVEFORM_SQUARE);
    channel1B.begin(0.3, 440, WAVEFORM_SAWTOOTH);

    audioFilter1C2.frequency(3000);
    audioFilter1C2.resonance(1);
    audioDelay1C1.delay(0, 0);
    masterMixer.gain(3, 0);
    masterMixer.gain(0, 0.5);

    lfo.begin(1, 3, WAVEFORM_SINE);

    AudioInterrupts();
}

void loop() {
    // SerialPortInterface::getData();

    // Main stuff
    int mainVolume = 1;

    codec.volume(mainVolume);

    int keyIndex = 0;
    int vcoOneOct = 1;
    int vcoTwoOct = 1;
    int deTune = 1;
    int deTuneLfo = 1;

    channel1A.frequency((noteFreq[keyIndex][keyIndex]/4)*vcoOneOct);
    channel1A.amplitude(1);
    channel1B.frequency(((noteFreq[keyIndex][keyIndex]/4*vcoTwoOct) * deTune) * deTuneLfo);
    channel1A.amplitude(1);

    // delay(100);
}