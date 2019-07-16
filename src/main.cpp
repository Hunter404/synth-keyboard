#define AUDIO
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define DEBUG
#define DEBUG_ALLOC

#ifdef AUDIO
  #include <Audio.h>

  // GUItool: begin automatically generated code
  AudioInputUSB            usb_in;         //xy=750,183
  AudioAmplifier           leftSlaveAmp;   //xy=2114,154
  AudioAmplifier           rightSlaveAmp;  //xy=2114,154
  AudioMixer4              slaveMixer;     //xy=1329,186
  AudioSynthWaveformSine   ringModulation; //xy=1391,411
  AudioEffectDelay         echo;           //xy=1423,720
  AudioEffectBitcrusher    bitcrush;       //xy=1593,296
  AudioMixer4              echoRepeat;     //xy=1594,566
  AudioEffectMultiply      ringModulationMultiplier; //xy=1596,404
  AudioEffectFreeverb      reverb;         //xy=1600,188
  AudioMixer4              reverbMixer;    //xy=1602,245
  AudioMixer4              bitcrushMixer;  //xy=1602,350
  AudioMixer4              ringModulationMixer; //xy=1602,457
  AudioMixer4              echoMixer;      //xy=1610,845
  AudioMixer4              masterMixer;    //xy=1892,155
  AudioFilterStateVariable cutoffFilter;   //xy=1897,874
  AudioMixer4              cutoffMixer;    //xy=2110,867
  AudioAmplifier           leftMasterAmp; //xy=2114,154
  AudioAmplifier           rightMasterAmp; //xy=2114,154
  AudioOutputUSB           usb_out;        //xy=2293,203
  AudioOutputI2S           i2s;            //xy=2294,100
  AudioConnection          patchCord1(usb_in, 0, leftSlaveAmp, 0);
  AudioConnection          patchCord2(usb_in, 1, rightSlaveAmp, 0);
  AudioConnection          patchCord1(leftSlaveAmp, 0, slaveMixer, 0);
  AudioConnection          patchCord2(rightSlaveAmp, 0, slaveMixer, 1);
  AudioConnection          patchCord3(slaveMixer, 0, reverb, 0);
  AudioConnection          patchCord4(slaveMixer, 0, reverbMixer, 1);
  AudioConnection          patchCord5(slaveMixer, 0, masterMixer, 1);
  AudioConnection          patchCord6(ringModulation, 0, ringModulationMultiplier, 1);
  AudioConnection          patchCord8(bitcrush, 0, bitcrushMixer, 0);
  AudioConnection          patchCord9(ringModulationMultiplier, 0, ringModulationMixer, 0);
  AudioConnection          patchCord10(reverb, 0, reverbMixer, 0);
  AudioConnection          patchCord11(reverbMixer, bitcrush);
  AudioConnection          patchCord12(reverbMixer, 0, bitcrushMixer, 1);
  AudioConnection          patchCord13(bitcrushMixer, 0, ringModulationMultiplier, 0);
  AudioConnection          patchCord14(bitcrushMixer, 0, ringModulationMixer, 1);
  AudioConnection          patchCord16(echoRepeat, 0, echo, 0);
  AudioConnection          patchCord17(ringModulationMixer, 0, echoRepeat, 0);
  AudioConnection          patchCord18(ringModulationMixer, 0, echoMixer, 1);
  AudioConnection          patchCord19(echo, 0, echoRepeat, 1);
  AudioConnection          patchCord20(echoRepeat, 0, echoMixer, 0);
  AudioConnection          patchCord21(echoMixer, 0, cutoffFilter, 0);
  AudioConnection          patchCord22(echoMixer, 0, cutoffMixer, 0);
  AudioConnection          patchCord23(cutoffFilter, 0, cutoffMixer, 1);
  AudioConnection          patchCord31(cutoffFilter, 2, cutoffMixer, 3);
  AudioConnection          patchCord25(cutoffMixer, 0, masterMixer, 0);
  AudioConnection          patchCord26(masterMixer, 0, leftMasterAmp, 0);
  AudioConnection          patchCord27(leftMasterAmp, 0, usb_out, 0);
  AudioConnection          patchCord28(rightMasterAmp, 0, usb_out, 1);
  AudioConnection          patchCord29(leftMasterAmp, 0, i2s, 0);
  AudioConnection          patchCord30(rightMasterAmp, 0, i2s, 1);
  AudioControlSGTL5000     sgtl5000;       //xy=1649,107
  // GUItool: end automatically generated code

  const int TOTAL_VOICES = 64;
  const int TOTAL_MIXERS = 21; // 64 / 4 = 16, + 16 / 4 = 4, + 4 / 4 = 1 = 21
  const int SECONDARY_MIXERS = 4; // What are these for

  AudioSynthWavetable wavetable[TOTAL_VOICES];
  AudioMixer4         mixer[TOTAL_MIXERS];
  AudioConnection patchCord[] = {
    {wavetable[0], 0, mixer[0], 0}, {wavetable[1], 0, mixer[0], 1}, {wavetable[2], 0, mixer[0],  2}, {wavetable[3], 0, mixer[0],  3}, {mixer[0], 0, mixer[TOTAL_MIXERS - 2], 0},
    {wavetable[4], 0, mixer[1], 0}, {wavetable[5], 0, mixer[1], 1}, {wavetable[6], 0, mixer[1],  2}, {wavetable[7], 0, mixer[1],  3}, {mixer[1], 0, mixer[TOTAL_MIXERS - 2], 1},
    {wavetable[8], 0, mixer[2], 0}, {wavetable[9], 0, mixer[2], 1}, {wavetable[10], 0, mixer[2],  2}, {wavetable[11], 0, mixer[2],  3}, {mixer[2], 0, mixer[TOTAL_MIXERS - 2], 2},
    {wavetable[12], 0, mixer[3], 0}, {wavetable[13], 0, mixer[3], 1}, {wavetable[14], 0, mixer[3],  2}, {wavetable[15], 0, mixer[3],  3}, {mixer[3], 0, mixer[TOTAL_MIXERS - 2], 3},
    {wavetable[16], 0, mixer[4], 0}, {wavetable[17], 0, mixer[4], 1}, {wavetable[18], 0, mixer[4],  2}, {wavetable[19], 0, mixer[4],  3}, {mixer[4], 0, mixer[TOTAL_MIXERS - 3], 0},
    {wavetable[20], 0, mixer[5], 0}, {wavetable[21], 0, mixer[5], 1}, {wavetable[22], 0, mixer[5],  2}, {wavetable[23], 0, mixer[5],  3}, {mixer[5], 0, mixer[TOTAL_MIXERS - 3], 1},
    {wavetable[24], 0, mixer[6], 0}, {wavetable[25], 0, mixer[6], 1}, {wavetable[26], 0, mixer[6],  2}, {wavetable[27], 0, mixer[6],  3}, {mixer[6], 0, mixer[TOTAL_MIXERS - 3], 2},
    {wavetable[28], 0, mixer[7], 0}, {wavetable[29], 0, mixer[7], 1}, {wavetable[30], 0, mixer[7],  2}, {wavetable[31], 0, mixer[7],  3}, {mixer[7], 0, mixer[TOTAL_MIXERS - 3], 3},
    {wavetable[32], 0, mixer[8], 0}, {wavetable[33], 0, mixer[8], 1}, {wavetable[34], 0, mixer[8],  2}, {wavetable[35], 0, mixer[8],  3}, {mixer[8], 0, mixer[TOTAL_MIXERS - 4], 0},
    {wavetable[36], 0, mixer[9], 0}, {wavetable[37], 0, mixer[9], 1}, {wavetable[38], 0, mixer[9],  2}, {wavetable[39], 0, mixer[9],  3}, {mixer[9], 0, mixer[TOTAL_MIXERS - 4], 1},
    {wavetable[40], 0, mixer[10], 0}, {wavetable[41], 0, mixer[10], 1}, {wavetable[42], 0, mixer[10], 2}, {wavetable[43], 0, mixer[10], 3}, {mixer[10], 0, mixer[TOTAL_MIXERS - 4], 2},
    {wavetable[44], 0, mixer[11], 0}, {wavetable[45], 0, mixer[11], 1}, {wavetable[46], 0, mixer[11], 2}, {wavetable[47], 0, mixer[11], 3}, {mixer[11], 0, mixer[TOTAL_MIXERS - 4], 3},
    {wavetable[48], 0, mixer[12], 0}, {wavetable[49], 0, mixer[12], 1}, {wavetable[50], 0, mixer[12], 2}, {wavetable[51], 0, mixer[12], 3}, {mixer[12], 0, mixer[TOTAL_MIXERS - 5], 0},
    {wavetable[52], 0, mixer[13], 0}, {wavetable[53], 0, mixer[13], 1}, {wavetable[54], 0, mixer[13], 2}, {wavetable[55], 0, mixer[13], 3}, {mixer[13], 0, mixer[TOTAL_MIXERS - 5], 1},
    {wavetable[56], 0, mixer[14], 0}, {wavetable[57], 0, mixer[14], 1}, {wavetable[58], 0, mixer[14], 2}, {wavetable[59], 0, mixer[14], 3}, {mixer[14], 0, mixer[TOTAL_MIXERS - 5], 2},
    {wavetable[60], 0, mixer[15], 0}, {wavetable[61], 0, mixer[15], 1}, {wavetable[62], 0, mixer[15], 2}, {wavetable[63], 0, mixer[15], 3}, {mixer[15], 0, mixer[TOTAL_MIXERS - 5], 3},
    {mixer[TOTAL_MIXERS - 2], 0, mixer[TOTAL_MIXERS - 1], 0},
    {mixer[TOTAL_MIXERS - 3], 0, mixer[TOTAL_MIXERS - 1], 1},
    {mixer[TOTAL_MIXERS - 4], 0, mixer[TOTAL_MIXERS - 1], 2},
    {mixer[TOTAL_MIXERS - 5], 0, mixer[TOTAL_MIXERS - 1], 3},
    {mixer[TOTAL_MIXERS - 1], 0, slaveMixer, 2},
    {mixer[TOTAL_MIXERS - 1], 0, slaveMixer, 3},
  };
#endif

#include "Arduino.h"

#include "io/io.h"
#include "io/ioTest.cpp"
#include "libs/serialport.cpp"
#include "instruments/Instruments.h"

using namespace Synth;

struct voice_t {
  int wavetable_id;
  byte channel;
  byte note;
};
voice_t voices[TOTAL_VOICES];

int used_voices = 0;
int stopped_voices = 0;
int evict_voice = 0;
int notes_played = 0;

const AudioSynthWavetable::instrument_data * const midi_map[] = {
  &piano, &piano, &piano, &piano, &piano, &piano, &piano, &piano, // 000: pianos
  &vibraphone, &vibraphone, &vibraphone, &vibraphone, &vibraphone, &vibraphone, &vibraphone, &vibraphone, // 008: chrom percus
  &harmonica, &harmonica, &harmonica, &harmonica, &harmonica, &harmonica, &harmonica, &harmonica, // 016: organs
  &nylonstrgtr, &steelstrgtr, &nylonstrgtr, &nylonstrgtr, &mutedgtr, &overdrivegt, &distortiongt, &nylonstrgtr, // 024: guitars
  &piano, &piano, &piano, &piano, &piano, &piano, &piano, &piano, // 032: bass
  &strings, &strings, &strings, &strings, &strings, &strings, &harp, &timpani, // 040: strings
  &strings, &strings, &strings, &strings, &strings, &strings, &strings, &strings, // 048: ensemble
  &trumpet, &trombone, &tuba, &frenchhorn, &frenchhorn, &frenchhorn, &frenchhorn, &frenchhorn, // 056: brass
  &oboe, &oboe, &oboe, &oboe, &oboe, &oboe, &bassoon, &clarinet, // 064: reed
  &flute, &flute, &recorder, &flute, &flute, &flute, &flute, &flute, // 072: pipe
  &piano, &piano, &piano, &piano, &piano, &piano, &piano, &piano, // 080: synth lead
  &piano, &piano, &piano, &piano, &piano, &piano, &piano, &piano, // 088: synth pad
  &piano, &piano, &piano, &piano, &piano, &piano, &piano, &piano, // 096: synth effect
  &piano, &piano, &piano, &piano, &piano, &piano, &piano, &piano, // 104: ethnic
  &timpani, &timpani, &timpani, &timpani, &timpani, &timpani, &timpani, &timpani, // 112: percussive
  &gtfretnoise, &gtfretnoise, &gtfretnoise, &gtfretnoise, &gtfretnoise, &gtfretnoise, &gtfretnoise, &gtfretnoise, // 120: sound effects
};

const AudioSynthWavetable::instrument_data * channel_map[17] = {
  &piano, &piano, &piano, &piano, &piano, &piano, &piano, &piano, &piano, &piano, &standard_DRUMS, &piano, &piano, &piano, &piano, &piano, &piano,
};

int channel_vol[] = {
  90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90
};

void OnControlChange(byte channel, byte control, byte value)
{
	switch (control) {
	case 7: //volume
		channel_vol[channel] = value;
		break;
	default:
		break;
	}
	Serial.print("Control Change, ch=");
	Serial.print(channel);
	Serial.print(", control=");
	Serial.print(control);
	Serial.print(", value=");
	Serial.print(value);
	Serial.println();
}


void OnProgramChange(byte channel, byte program) {
	channel_map[channel] = channel != 10 ? midi_map[program] : &standard_DRUMS;
}

int allocateVoice(byte channel, byte note) {
  int i;
  int nonfree_voices = stopped_voices + used_voices;
  if (nonfree_voices < TOTAL_VOICES) {
    for (i = nonfree_voices; i < TOTAL_VOICES && voices[i].channel != channel; ++i);
    if (i < TOTAL_VOICES) {
      voice_t temp = voices[i];
      voices[i] = voices[nonfree_voices];
      voices[nonfree_voices] = temp;
    }
    i = nonfree_voices;
    used_voices++;
  }
  else {
    if (stopped_voices) {
      i = evict_voice % stopped_voices;
      voice_t temp = voices[i];
      stopped_voices--;
      voices[i] = voices[stopped_voices];
      voices[stopped_voices] = temp;
      used_voices++;
      i = stopped_voices;
    }
    else
      i = evict_voice;
  }

  voices[i].channel = channel;
  voices[i].note = note;

  evict_voice++;
  evict_voice %= TOTAL_VOICES;

  return voices[i].wavetable_id;
}

int findVoice(byte channel, byte note) {
  int i;
  //find match
  int nonfree_voices = stopped_voices + used_voices;
  for (i = stopped_voices; i < nonfree_voices && !(voices[i].channel == channel && voices[i].note == note); ++i);
  //return TOTAL_VOICES if no match
  if (i == (nonfree_voices)) return TOTAL_VOICES;

  voice_t temp = voices[i];
  voices[i] = voices[stopped_voices];
  voices[stopped_voices] = temp;
  --used_voices;

  return voices[stopped_voices++].wavetable_id;
}

void freeVoices() {
  for (int i = 0; i < stopped_voices; i++)
    if (wavetable[voices[i].wavetable_id].isPlaying() == false) {
      voice_t temp = voices[i];
      --stopped_voices;
      voices[i] = voices[stopped_voices];
      int nonfree_voices = stopped_voices + used_voices;
      voices[stopped_voices] = voices[nonfree_voices];
      voices[nonfree_voices] = temp;
    }
}

void guitarHeroMode() { // now unicorn friendly
	const int RESET = 4;
	const int MIDI_NOTES = 128;
	static char line[MIDI_NOTES + 1] = { 0 };
	static int accumulated = 0;
	if (!accumulated) {
		for (int i = 0; i < MIDI_NOTES; ++i) line[i] = '-';
		++accumulated;
	}
	for (int i = stopped_voices; i < used_voices + stopped_voices; ++i) line[voices[i].note] = '*';
	if (accumulated == RESET) {
		Serial.println(line);
		accumulated = 0;
	}
	else {
		++accumulated;
	}
}

const char* note_map[] = {
  "C","C#","D","D#","E","F","F#","G","G#","A","A#","B"
};

void printVoices() {
	static int last_notes_played = notes_played;
	if (last_notes_played == notes_played)
		return;
	last_notes_played = notes_played;
	int usage = AudioProcessorUsage();
	Serial.printf("CPU:%03i voices:%02i CPU/Voice:%02i evict:%02i", usage, used_voices, usage / used_voices, evict_voice);
	for (int i = 0; i < used_voices; ++i)
		Serial.printf(" %02hhu %-2s", voices[i].channel, note_map[voices[i].note % 12]);

  Serial.println();
}

void changeVoice(byte channel, byte program)
{
  channel_map[channel] = channel != 10 ? midi_map[program] : &standard_DRUMS;
}

void playNote(byte channel, byte note, byte velocity)
{
  notes_played++;

#ifdef DEBUG_ALLOC
  //Serial.printf("**** NoteOn: channel==%hhu,note==%hhu ****\n", channel, note);
  printVoices();
#endif //DEBUG_ALLOC

  freeVoices();
  int wavetable_id = allocateVoice(channel, note);
  wavetable[wavetable_id].setInstrument(*channel_map[channel]);
  wavetable[wavetable_id].playNote(note, (velocity*channel_vol[channel] + 0x80) >> 7);

#ifdef DEBUG_ALLOC
  printVoices();
#endif //DEBUG_ALLOC
}

void stopNote(byte channel, byte note)
{
#ifdef DEBUG_ALLOC
	//Serial.printf("\n**** NoteOff: channel==%hhu,note==%hhu ****", channel, note);
	printVoices();
#endif //DEBUG_ALLOC

  int wavetable_id = findVoice(channel, note);
  if (wavetable_id != TOTAL_VOICES)
    wavetable[wavetable_id].stop();

#ifdef DEBUG_ALLOC
  printVoices();
#endif //DEBUG_ALLOC
}

TrellisCallback tone(keyEvent evt)
{
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING)
  {
    IO::trellis.setPixelColor(evt.bit.NUM, IO::wheel(map(evt.bit.NUM, 0, NEOTRELLIS_X_DIM*NEOTRELLIS_Y_DIM, 0, 255)));
    IO::trellis.show();

    playNote(0, evt.bit.NUM, 255);
  }
  else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING)
  {
    IO::trellis.setPixelColor(evt.bit.NUM, 0);
    IO::trellis.show();

    stopNote(0, evt.bit.NUM);
  }


  return 0;
}

void setup() {
  pinMode(13, OUTPUT);

  // Serial Port
  SerialPortInterface::start();

  // IO
  IO::setup();

  for (int x = 0; x < NEOTRELLIS_X_DIM; x++) {
    for (int y = 0; y < NEOTRELLIS_Y_DIM; y++) {
      IO::trellis.registerCallback(x, y, tone);
    }
  }

  // IOTest::test();

  // Audio
  for (int i = 0; i < TOTAL_VOICES; ++i) {
    wavetable[i].setInstrument(nylonstrgtr);
    wavetable[i].amplitude(1.0f);
    voices[i].wavetable_id = i;
    voices[i].channel = voices[i].note = 0xFF;
  }

  for (int i = 0; i < TOTAL_MIXERS - 1; ++i)
    for (int j = 0; j < 4; ++j)
      mixer[i].gain(j, 3);

  for (int i = 0; i < 4; ++i)
    mixer[TOTAL_MIXERS - 1].gain(i, 3); // .gain(i, i < SECONDARY_MIXERS ? 2.0f / SECONDARY_MIXERS : 0.0f);

  OnControlChange(0, 7, 255);

  for (int i = 0; i < 16; i++)
    OnProgramChange(i, 10);


  AudioNoInterrupts();
  AudioMemory(360);

  ringModulation.amplitude(1);

  echoRepeat.gain(0, 1);
  echoRepeat.gain(1, 0.5);

  slaveMixer.gain(2, 1);
  slaveMixer.gain(3, 1);

  sgtl5000.enable();
  sgtl5000.volume(0.7);

  AudioInterrupts();
}

static uint32_t next;
static bool led;

bool echoEnabled = true;
bool reverbEnabled = true;
bool cutoffEnabled = true;
bool ringModulationEnabled = true;
bool bitcrushEnabled = true;
bool distortionEnabled = true;
bool beatrepeaterEnabled = true;
bool overallEnabled = true;

float echoValLast = 0.0f;
float reverbValLast = 0.0f;
float cutoffValLast = 0.0f;
float ringModulationValLast = 0.0f;
float bitcrushValLast = 0.0f;
float distortionValLast = 0.0f;
float beatrepeaterValLast = 0.0f;
float overallValLast = 0.0f;

typedef void (* vUpdateFilter)(float args);

bool changed(float input, float &other)
{
  if (fabsf(input - other) <= __FLT_EPSILON__) return false;

  other = input;

  return true;
}

void updateCutoff(float input)
{

  if (input > 0.52f)
  {
    float hipass = map(input, 0.52f, 1.0f, 0.0f, 1.0f);

    cutoffMixer.gain(0, 1 - hipass);
    cutoffMixer.gain(1, 0);
    cutoffMixer.gain(3, hipass);
  }
  else if (input < 0.48f)
  {
    float lopass = map(input, 0.48f, 0.0f, 0.0f, 1.0f);

    cutoffMixer.gain(0, 1 - lopass);
    cutoffMixer.gain(1, lopass);
    cutoffMixer.gain(3, 0);
  }
  else
  {
    cutoffMixer.gain(0, 1);
    cutoffMixer.gain(1, 0);
    cutoffMixer.gain(2, 0);
    cutoffMixer.gain(3, 0);
  }
}

void updateReverb(float input)
{
  reverb.roomsize(input);
}

void updateBitcrush(float input)
{
  bitcrush.bits((uint8_t) ((1 - bitcrushValLast) * 16));
  bitcrush.sampleRate((1 - distortionValLast) * 44100);
}

void updateEcho(float input)
{
  echo.delay(0, roundf(input * 500));
}

void updateRingModulation(float input)
{
  ringModulation.frequency((int) (input * 10));
}

void updateDistortion(float input)
{
  bitcrush.sampleRate((1 - input) * 44100.0f);
}

void updateFilter(bool &enabled, float input, float off, AudioMixer4 *mixer, AudioConnection *a, AudioConnection *b, void (*func)(float))
{
  if (fabsf(input - off) > __FLT_EPSILON__)
  {
    if (!enabled)
    {
      if (a) a->connect();
      if (b) b->connect();

      enabled = true;
    }

    if (func) func(input);

    if (mixer)
    {
      mixer->gain(0, map(input, 1.0f, 0.0f, 1.0f, 0.0f));
      mixer->gain(1, map(input, 0.0f, 1.0f, 1.0f, 0.0f));
    }
  }
  else
  {
    if (enabled)
    {
      if (a) a->disconnect();
      if (b) b->disconnect();

      if (mixer)
      {
        mixer->gain(0, 0);
        mixer->gain(1, 1);
      }

      if (func) func(off);

      enabled = false;
    }
  }
}

void loop() {
  SerialPortInterface::getData();

  IO::update();

  float volume = IO::readPot(13) * 1.5f;

  float bpmVal = IO::readSlidePot(1);
  float echoVal = IO::readSlidePot(2);
  float reverbVal = IO::readSlidePot(3);
  float cutoffVal = IO::readSlidePot(4);
  float ringModulationVal = IO::readSlidePot(5);
  float bitcrushVal = IO::readSlidePot(6);
  float distortionVal = IO::readSlidePot(7);
  float beatrepeaterVal = IO::readSlidePot(8);
  float overallVal = IO::readSlidePot(9);

  AudioNoInterrupts();

  if (changed(reverbVal, reverbValLast))
    updateFilter(reverbEnabled, reverbVal, 0, &reverbMixer, &patchCord3, &patchCord10, &updateReverb);

  if (changed(bitcrushVal, bitcrushValLast) || changed(distortionVal, distortionValLast))
    updateFilter(bitcrushEnabled, max(bitcrushVal, distortionVal), 0, &bitcrushMixer, &patchCord8, &patchCord11, &updateBitcrush);

  if (changed(ringModulationVal, ringModulationValLast))
    updateFilter(ringModulationEnabled, ringModulationVal, 0, &ringModulationMixer, &patchCord9, &patchCord13, &updateRingModulation);

  if (changed(echoVal, echoValLast))
    updateFilter(echoEnabled, echoVal, 0, &echoMixer, &patchCord17, &patchCord20, &updateEcho);

  if (changed(cutoffVal, cutoffValLast))
    updateFilter(cutoffEnabled, cutoffVal, 0.5f, nullptr, &patchCord21, nullptr, &updateCutoff);

  if (changed(overallVal, overallValLast))
    updateFilter(overallEnabled, overallVal, 0, &masterMixer, nullptr, nullptr, nullptr);

  masterAmplifier.gain(volume);

  AudioInterrupts();

  if(millis() > next)
  {
    next = millis() + 1000;

    if (led)
      led = 0;
    else
      led = 1;

    digitalWrite(13, led);

    Serial.println(AudioMemoryUsageMax());
  }

  delay(20);
}
